#include "Document.h"

void Document::addSubNote(Note *n){
    if(isNote(n))
        return;

    content.push_back(n);
    modified = true;
}

void Document::addSubNote(Note *n, unsigned int pos){
    if(isNote(n))
        return;

    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    content.insert(it, n);
    modified = true;
}

void Document::removeSubNote(unsigned int pos){
    load();    
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    content.erase(it);
    modified = true;
}

void Document::removeSubNote(const Note* n){
    load();
    for(std::list<Note*>::iterator it = content.begin(); it != content.end() ; it++)
        if(*it == n){
            content.erase(it);
            modified = true;
        }
}

Note* Document::getSubNote(unsigned int pos){
    load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    return *it;
}

bool Document::isNote(const Note* n){
    for(std::list<Note*>::iterator it = content.begin(); it != content.end() ; it++)
        if(*it == n)
            return true;
    return false;
}

bool Document::isNote(const QString& id){
    for(std::list<Note*>::iterator it = content.begin(); it != content.end() ; it++)
        if(((Note*)*it)->getId() == id)
            return true;
    return false;
}

void Document::load(){
    //Si la note est déjà chargée on ne le recharge pas
    if(getLoaded())
        return;

    //récupère les information pouvant manquer comme la liste des notes
    //Vérifie si on a besoin d'annalyser le fichier (liste pleine)
    if(content.size() > 0)
        return;

    QFile fichier(getWS() + getId());

    //on sort si le fichier n'existe pas
    if(!fichier.exists())
        return;

    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
        throw NotesException("Can't open document file");
    }

     QTextStream flux(&fichier);
     //saute la première ligne
     flux.readLine();
     while(!flux.atEnd()){
         //Pour chaques ligne, enregistre la note et l'ajoute au document
          QString subfile = flux.readLine();
          //vérifie que le fichier n'est pas déjà dans la liste
          if(isNote(subfile))
              //passe au fichier suivant
              continue;

          //si fichier non présent dans la liste
          //création d'une note en mémoire, catcher les exceptions
          Note& note = NotesManager::getInstance()->getNote(subfile);
          //ajoute le fichier à la liste
          addSubNote(&note);
     }

     setLoaded(true);
}

QTextStream& Document::save(QTextStream& f){
    f<<this->getTitle()<<"\n";

    for(std::list<Note*>::iterator it = content.begin(); it != content.end(); it++)
        f<<(*it)->getId()<<"\n";

    return f;
}

NoteEditor* Document::getEditor(QWidget* parent){
    load();
    return new DocumentEditor(this, parent);
}

void Document::makehtmlbody(QXmlStreamWriter* qw){
    qw->writeTextElement("h1", getTitle());
    qw->writeEmptyElement("br");
    for(std::list <Note*>::const_iterator it=content.begin();it!=content.end();++it){
        qw->writeEmptyElement("hr");
        qw->writeEmptyElement("br");
        //insÃ©rer ici la partie relative a chaque Ã©lÃ©ment de content
        dynamic_cast<Note*>(*it)->makehtmlbody(qw);
        qw->writeEmptyElement("br");
    }
}

QString Document::toTEX(){
    QString x;
    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }
    createTexHeader(buffer);
    for(std::list <Note*>::const_iterator it=content.begin();it!=content.end();++it){
        x=dynamic_cast<Note*>(*it)->toTEX();
        x=x.left(x.indexOf("\\end{document}",0));
        x=x.right(x.length()-(x.indexOf("\\begin{document}",0)+16));
        x.push_front("\n");
        x.push_front("\n");
        buffer->write(x.toAscii());
    }
    buffer->write("\\end{document}\n");
    buffer->close();
    return QString(*file);
}

QString Document::toTEXT(){
    QString out = getTitle() + "\n";
    for(std::list <Note*>::const_iterator it=content.begin();it!=content.end();++it){
        out += "\n##################################################\n";
        out += "\n" + ((Note*)(*it))->toTEXT() + "\n";
    }

    return out;
}

DocumentEditor::DocumentEditor(Document* d, QWidget* parent):NoteEditor(d, parent){
    setParent(parent);
    QPushButton *insert = new QPushButton("Ajouter une note", this);
    zone->layout()->addWidget(insert);
    QObject::connect(insert, SIGNAL(clicked()), this, SLOT(selectNote()));

    //Charger toutes les widgets des notes dans la liste content    
    for(unsigned int i = 0; i < d->getNbSubNotes(); i++){
        //pour chaques sous-notes insère l'Editeur associé
        insertNote(d->getSubNote(i)->getEditor(this));
    }
}

void DocumentEditor::detachNote(QWidget *wid){
    zone->layout()->removeWidget(wid);
    ((Document*)ressource)->removeSubNote(&((NoteEditor*)wid)->getRessource());
    wid->hide();
}

void DocumentEditor::selectNote(){
    //demande à l'utilisateur de sélectionner une note parmi celles listées ou d'en créer une
    NotesManager *manager = NotesManager::getInstance();

    //fenêtre de sélection
    ask = new QDialog;
    ask->setWindowTitle("Selectionner une note à ajouter");
    ask->setLayout(new QVBoxLayout);

    //partie texte
    ask->layout()->addWidget(new QLabel("Veuillez choisir une note à ajouter:", ask));

    //partie listes
    QWidget *listes = new QWidget(ask);
    listes->setLayout(new QHBoxLayout);
    ask->layout()->addWidget(listes);

    notes = new QListEditor(listes);
    listes->layout()->addWidget(notes);

    //lister les notes existantes - celle déjà dans le document
    for(unsigned int i = 0; i < manager->getNbNotes(); i++){
        Note *n = manager->getNote(i);
        //si la note ne fait pas partie de celle du document et que ce n'est pas lui même
        if(!((Document*)ressource)->isNote(n) && n != ressource)
            notes->addItem(new QListEditorItem(manager->getNoteIcon(n), n->getTitle(), n->getEditor(), notes));
    }

    QObject::connect(notes, SIGNAL(itemDoubleClicked(QListWidgetItem*)), notes, SLOT(itActDoubleClicked(QListWidgetItem*)));
    QObject::connect(notes, SIGNAL(itActDoubleClickedS(QListEditorItem*)), this, SLOT(openNote(QListEditorItem*)));

    ask->exec();
}

void DocumentEditor::insertNote(NoteEditor *ne, QWidget *parent){
    //insérer une note à la suite
    QWidget *subNote = new QWidget(parent);
    subNote->move(this->pos() + QPoint(10, 0));
    subNote->setLayout(new QVBoxLayout);

    DocButton *detach = new DocButton(subNote, "Detacher la note ci-dessous", subNote);
    subNote->layout()->addWidget(detach);

    QObject::connect(detach, SIGNAL(clicked()), detach, SLOT(getWid()));
    QObject::connect(detach, SIGNAL(sendWid(QWidget*)), this, SLOT(detachNote(QWidget*)));

    ((Document*)ressource)->addSubNote(&(ne->getRessource()));

    subNote->layout()->addWidget(ne);
    ne->show();
    zone->layout()->addWidget(subNote);

    if(ask)
        ask->close();
}

void DocumentEditor::openNote(QListEditorItem *nt){
    insertNote(nt->getRessource(), ask);
}

void DocButton::getWid(){
    emit sendWid(widget);
}
