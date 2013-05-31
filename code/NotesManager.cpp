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
       //Récupérer son type dans le fichier workspace
       QString type;
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

    n = noteConstructor(type, getId(), title);

    if(n == NULL)
        throw NotesException("Can't create a note of type: " + type);

    addNote(n);
    return *n;
}

Note* NotesManager::noteConstructor(const QString& type, const QString& id, const QString& title){
    //Rajouter les types ici ...

    if(type == "Article"){
        return new Article(id, title);
    } else if(type == "Document"){
        return new Document(id, title);
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
    return "" + id;
}

NotesManager* NotesManager::instance=0; // pointeur sur l'unique instance
NotesManager& NotesManager::getInstance(){
    if (!instance) instance=new NotesManager;
    return *instance;
}

void NotesManager::libererInstance(){
    if (instance) delete instance;
    instance=0;
}

NotesManager::~NotesManager(){
    for(std::set<Note*>::iterator it=notes.begin(); it != notes.end(); it++){
        saveNote(*(*it));
        delete *it;
    }

    notes.clear();
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
    }
}

