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
    //récupère les information pouvant manquer comme la liste des notes
    //Vérifie si on a besoin d'annalyser le fichier (liste pleine)
    if(content.size() > 0)
        return;

    QFile fichier(getId());

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
}

QTextStream& Document::save(QTextStream& f){
    f<<this->getTitle()<<"\n";

    for(std::list<Note*>::iterator it = content.begin(); it != content.end(); it++)
        f<<(*it)->getId()<<"\n";

    return f;
}

QString Document::toHTML(){
    QXmlStreamWriter* qw=new QXmlStreamWriter;


    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }
    createHtmlTree(buffer);
    for(std::list <Note*>::const_iterator it=content.begin();it!=content.end();++it){
        qw->writeEmptyElement("br");
        qw->writeTextElement("h1",QString("Titre:")+**it.getTitle());
        qw->writeTextElement("h2",QString("ID:")+**it.getId());
        qw->writeTextElement("p",*it.getContent());
        //qw->writeTextElement("p",QString("Tag:")+*it.getTags());
        qw->writeEmptyElement("br");
    }
    endHtmlTree(buffer);
    buffer->close();
    return QString(*file);

}

QString Document::toTEX(){
    return "";
}

QString Document::toTEXT(){
    return "";
}

DocumentEditor::DocumentEditor(Document* d, QWidget* parent):NoteEditor(d, parent){
    title = new QLineEdit(this);
    title->setText(d->getTitle());
    zone->layout()->addWidget(title);

    //Charger toutes les widgets des notes dans la liste content
}

void DocumentEditor::update(QString s){

}
