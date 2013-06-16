#include "Document.h"
#include "NotesManager.h"

void Document::addSubNote(Note *n){
    load();
    content.push_back(n);
    modified = true;
}

void Document::addSubNote(Note *n, unsigned int pos){
    load();
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

Note* Document::getSubNote(unsigned int pos){
    load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    return *it;
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
          for(std::list<Note*>::iterator it = content.begin(); it != content.end(); it++)
              if((*it)->getId() == subfile)
                  //passe au fichier suivant
                  continue;

          //si fichier non présent dans la liste
          //création d'une note en mémoire, catcher les exceptions
          Note& note = NotesManager::instance->getNote(subfile);

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
    return new DocumentEditor(this, parent);
}

void Document::makehtmlbody(QXmlStreamWriter* qw){
    for(std::list <Note*>::const_iterator it=content.begin();it!=content.end();++it){
        qw->writeEmptyElement("br");
        //insÃ©rer ici la partie relative a chaque Ã©lÃ©ment de content
        dynamic_cast<Note*>(*it)->makehtmlbody(qw);
        qw->writeEmptyElement("br");
        qw->writeEmptyElement("hr");
    }
}

QString Document::toTEX(){
    QString x;
    int i;
    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }
    createTexHeader(buffer);
    for(std::list <Note*>::const_iterator it=content.begin();it!=content.end();++it){
        x=dynamic_cast<Note*>(*it)->toHTML();
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
    QString out = "";
    for(std::list <Note*>::const_iterator it=content.begin();it!=content.end();++it){
        out += "\n" + ((Note*)(*it))->toTEXT();
        out += "\n##################################################";
    }

    return out;
}

DocumentEditor::DocumentEditor(Document* d, QWidget* parent):NoteEditor(d, parent){
    setParent(parent);
    QPushButton *insert = new QPushButton("Inserer une note ici", this);
    zone->layout()->addWidget(insert);
    QObject::connect(insert, SIGNAL(clicked()), insert, SLOT(selectNote()));

    //Charger toutes les widgets des notes dans la liste content    
    for(unsigned int i = 0; i < d->getNbSubNotes(); i++){
        //pour chaques sous-notes insère l'Editeur associé
        insertNote(d->getSubNote(i)->getEditor(this));
    }
}

void DocumentEditor::detachNote(QWidget *wid){
    zone->layout()->removeWidget(wid);
    wid->hide();
}

void DocumentEditor::selectNote(){
    //demande à l'utilisateur de sélectionner une note parmi celles listées ou d'en créer une
    NotesManager *manager = NotesManager::getInstance();

    //fenêtre de sélection
    QDialog ask;
    ask.setWindowTitle("Selectionner une note à ajouter");
    ask.setLayout(new QVBoxLayout);

    //partie texte
    ask.layout()->addWidget(new QLabel("Veuillez choisir une note à ajouter:", this));

    //partie listes
    QWidget *listes = new QWidget(this);
    listes->setLayout(new QHBoxLayout);
    ask.layout()->addWidget(listes);

    QListWidget *notes = new QListWidget(listes);
    listes->layout()->addWidget(notes);

    //lister les notes existantes - celle déjà dans le document

    //partie boutons
    QWidget *buttons = new QWidget(this);
    buttons->setLayout(new QHBoxLayout);

    QPushButton *article = new QPushButton(ico_article, "");
    article->setToolTip("Créer un nouvel article");
    buttons->layout()->addWidget(article);

    QPushButton *document = new QPushButton(ico_document, "");
    document->setToolTip("Créer un nouveau document");
    buttons->layout()->addWidget(document);

    QPushButton *image = new QPushButton(ico_image, "");
    image->setToolTip("Créer une nouvelle note image");
    buttons->layout()->addWidget(image);

    QPushButton *audio = new QPushButton(ico_audio, "");
    audio->setToolTip("Créer une nouvelle note audio");
    buttons->layout()->addWidget(audio);

    QPushButton *video = new QPushButton(ico_video, "");
    video->setToolTip("Créer une nouvelle note vidéo");
    buttons->layout()->addWidget(video);

    ask.layout()->addWidget(buttons);

    /*QObject::connect(workspaces, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showNotes(QListWidgetItem*)));
    QObject::connect(workspaces, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(showNotes(QListWidgetItem*)));
    QObject::connect(open, SIGNAL(clicked()), this, SLOT(loadWS()));
    QObject::connect(clone, SIGNAL(clicked()), this, SLOT(cloneWS()));
    QObject::connect(del, SIGNAL(clicked()), this, SLOT(safeDel()));
    QObject::connect(create, SIGNAL(clicked()), this, SLOT(newWS()));*/

    ask.exec();
}

void DocumentEditor::insertNote(QWidget *wid){
    //insérer une note à la suite
    QWidget *subNote = new QWidget(zone);
    subNote->move(this->pos() + QPoint(10, 0));
    subNote->setLayout(new QVBoxLayout);

    DocButton *detach = new DocButton(subNote, "Detacher la note ci-dessous", subNote);
    subNote->layout()->addWidget(detach);

    QObject::connect(detach, SIGNAL(clicked()), detach, SLOT(getWid()));
    QObject::connect(detach, SIGNAL(sendWid(QWidget*)), this, SLOT(detachNote(QWidget*)));

    subNote->layout()->addWidget(wid);
    zone->layout()->addWidget(subNote);
}

void DocButton::getWid(){
    emit sendWid(widget);
}
