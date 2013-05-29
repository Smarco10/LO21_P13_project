#include "NotesManager.h"

void NotesManager::addNote(const Note& n){
    notes.insert(n);
}

Note& NotesManager::getNote(const unsigned int id){
   std::set<Note>::iterator it= notes.find(id);
   if(it==notes.end())
   {    //ouberture de la note existante
       QFile fichier(id);
       fichier.open(QIODevice::ReadOnly | QIODevice::Text);// sur pour les parametres?
       QTextStream flux(&fichier);
       QString title=flux.readLine();
       Note* n=new Note(id,title);
       addNote(n);
       return *n;
    }
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

Note& NotesManager::getNewNote(QString title){
    Note* n=new Note(QTime::currentTime().toString(),title);
    n->modified=true;
    addNote(d);
    return *d;
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


NotesManager::NotesManager()
{}


NotesManager::~NotesManager(){
    for(unsigned int i=0; i<nbDocuments; i++){
        saveDocument(*documents[i]);
        delete documents[i];
    }
    for(unsigned int i=0; i<nbArticles; i++) {
        saveArticle(*articles[i]);
        delete articles[i];
    }
    delete[] documents;
    delete[] articles;
}

void NotesManager::saveArticle(Article& a){
    if (a.isModified()) {
        // Création d'un objet QFile
        QFile file(a.getFilename());
        // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un article : impossible d'ouvrir un fichier en écriture");
        QTextStream flux(&file);
        flux<<a;
        file.close();
        a.modified=false;
    }
}

void NotesManager::saveDocument(Document& d){
    if (d.isModified()) {
        // Création d'un objet QFile
        QFile file(d.getFilename());
        // On ouvre notre fichier en lecture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'un document : impossible d'ouvrir un fichier en écriture");
        QTextStream flux(&file);
        flux<<d;
        file.close();
        d.modified=false;
    }
}
//*/
Note<set>::iterator::operator==(Notes<set>::Iterator it){

}
