#include "NotesManager.h"

void NotesManager::addNote(const Note* n){
    notes.insert(n);
    n->modified = false;
}

Note& NotesManager::getNote(QString id){
    //regarde si la note est dans la liste
   std::set<Note*>::iterator it= notes.find(id);

   if(it==notes.end())
   {
       //si note non existante dans la liste on la charge et si elle n'existe pas on la crée
       //Récupérer son type dans le fichier workspace
       typeNote(id);

       QString title = "";

       QFile fichier(id);
       if(fichier.exists()){
           if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
                //si fichier n'a pu être ouvert, on créer une nouvelle Note
               throw NotesException("Error can't open Note file");
           }
           QTextStream flux(&fichier);
           title = flux.readLine();

           fichier.close();
       } else {
           id = getId();
       }

       Note* n = NULL;

       switch(type){
       case "Article":
           if(title == "") title = "Article_" + id;
           n = new Article(id, title);
           break;
       case "Document":
           if(title == "") title = "Document_" + id;
           n = new Document(id, title);
           break;
       default:
           //type inconnu on laisse à NULL
           break;
       }

       addNote(n);
       return *n;
    }

    return *it;

    /* // on vérifie d'abord que le document demandé n'a pas déjà été chargé
   // notes.iterator it=notes.find(filename);
    if(it==it.end){// a arranger avec un operateur de comparaison ou autre
    QFile fichier(fileName);
    fichier.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&fichier);
    QString title=flux.readLine();
    Note* d=new Note(fileName,title);
    QString ligne;
    while(! flux.atEnd())
    {
        ligne = flux.readLine();
        (*d)<<(getArticle(ligne));

    }
    addNote(n);
    return *n;
}*/
}

QString getId(){
    return QString::number(QDateTime::currentMSecsSinceEpoch());
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
    for(std::set<Note*>::iterator it=notes.begin(); it < notes.end(); it++){
        saveNote(*it);
        delete *it;
    }

    notes.clear();
}

void NotesManager::saveNote(Note& n){
    if (n.isModified()) {
        // Création d'un objet QFile
        QFile file(n.getFilename());
        // On ouvre notre fichier en écriture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'une note : impossible d'ouvrir un fichier en écriture");
        QTextStream flux(&file);
        flux<<n;
        file.close();
        n.modified=false;
    }
}

