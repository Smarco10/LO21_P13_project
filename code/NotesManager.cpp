#include "NotesManager.h"

void NotesManager::addNote(Note* n){
    notes.insert(n);
    n->setModified(true);
}

Note& NotesManager::getNote(QString& id){
    //regarde si la note est dans la liste
   std::set<Note*>::iterator it= notes.end()/*notes.find(id)*/;

   if(it==notes.end())
   {
       //si note non existante dans la liste on la charge et si elle n'existe pas on la crée
       //Récupère le type dans le fichier workspace
       QString type = workspace->getType(id);
       QString title;
       Note* n = NULL;

       QFile fichier(id);
       if(fichier.exists()){
           if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
                //si fichier n'a pu être ouvert, on créer une nouvelle Note
               throw NotesException("Error can't open Note file");
           }

           QTextStream flux(&fichier);
           title = flux.readLine();

           fichier.close();

           //on récupère le type de la note
           type = typeNote(id);
       } else {
           //Erreur
           throw NotesException("File doesn't exist");
       }

       n = noteConstructor(type, id, title);
       if(n == NULL)
           NotesException("Can't create a note of type: " + type);

       addNote(n);
       return *n;
    }

    return *(*it);
}

Note& NotesManager::getNewNote(const QString& type, const QString& title){
    Note* n = NULL;
    QString id = getId();

    n = noteConstructor(type, id, (title.isEmpty()) ? QString(type + "_" + id) : title);
    printf("titleNM = %s\n", n->getTitle().toStdString().c_str());
    if(n == NULL)
        throw NotesException("Can't create a note of type: " + type);

    addNote(n);

    return *n;
}

Note* NotesManager::noteConstructor(const QString& type, const QString& id, const QString& title){
    //Rajouter les types ici ...

    printf("titleNC = %s\n", title.toStdString().c_str());

    if(type == "Article"){
        return new Article(id, title);
    } else if(type == "Document"){
        return new Document(id, title);
    } else if(type == "Image"){
        return new Image(id, title);
    } else if(type == "Audio"){
        return new Audio(id, title);
    } else if(type == "Image"){
        return new Video(id, title);
    }

    //type inconnu on laisse à NULL
    return NULL;
}

QString NotesManager::getId(){
    //retourne le l'heure locale en miliseconde depuis 1970 dans un QString
    return QString::number(QDateTime::currentMSecsSinceEpoch());
}

QString NotesManager::typeNote(const QString& id){
    //récupérer le type de la note dans le fichier workspace en XML
    return workspace->getType(id);
}

Workspace* NotesManager::workspace = NULL;
NotesManager* NotesManager::instance = NULL; // pointeur sur l'unique instance
NotesManager& NotesManager::getInstance(){
    if(!workspace) workspace = new Workspace;
    loadWSNotes();
    if(!instance) instance=new NotesManager;
    return *instance;
}

void NotesManager::libererInstance(){
    if (instance) delete instance;
    instance=0;
}

NotesManager::~NotesManager(){
    //sauvegarde toutes les notes et le workspace avant de quitter
    reset();
}

void NotesManager::reset(){
    for(std::set<Note*>::iterator it=notes.begin(); it != notes.end(); it++){
        saveNote(*(*it));
        delete *it;
    }

    notes.clear();
    delete workspace;
}

void NotesManager::saveNote(Note& n){
    if (n.isModified()) {
        // Création d'un objet QFile
        QFile file(n.getId());

        // On ouvre notre fichier en écriture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'une note : impossible d'ouvrir un fichier en écriture");

        QTextStream flux(&file);
        flux<<n;
        file.close();
        n.setModified(false);

        //met à jour la note dans le workspace (implémenter les tags
        workspace->addNote(n.getId(), n.getType(), "");
    }
}

void NotesManager::loadWSNotes(){
    //charger tt les éléments du workspace
    QString lst_notes = " " + workspace->listNotes();

    if(lst_notes.isEmpty())
        return;

    //toutes les notes sont séparées par des '\n'
    int offset = 1;
    while(offset + 1 < lst_notes.size()){
        //récupère la note
        QString note = lst_notes.mid(offset, lst_notes.indexOf(QChar('\n'), offset));
        //enlève le caractère '\n' résiduel de l'opération précédente
        if(note.at(note.size() - 1) == QChar('\n')) note.remove(note.size() - 1, 1);
        //ajout de la note
        instance->getNote(note);
        offset = lst_notes.indexOf(QChar('\n'), offset) + 1;
    }
}

void NotesManager::changeWorkSpace(const QString& path){
    //vider la liste de notes en sauvant toutes les notes et le workspace <=> suppression
    instance->reset();

    //Création du nouveau workspace
    workspace = new Workspace(path);

    //vérifier l'intégrité du fichier workspace
    workspace->check();

    //charger toutes les notes du workspace si tout vas bien.
    loadWSNotes();
}
