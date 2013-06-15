#include "NotesManager.h"

void NotesManager::addNote(Note* n){
    notes.insert(n);
    n->setModified(true);
}

void NotesManager::removeNote(Note *n){
    for(std::set<Note*>::iterator it=notes.begin(); it != notes.end(); it++)
        if(*it == n){
            notes.erase(it);
            break;
        }
    n->setModified(true);
}

Note* NotesManager::getNote(unsigned int i){
    //récupère la ième note du set
    unsigned int cmp = 0;
    for(std::set<Note*>::iterator it = notes.begin(); it != notes.end(); it++)
        if(cmp++ == i)
            return *it;

    return NULL;
}

Note& NotesManager::getNote(const QString& id){
    //regarde si la note est dans la liste
   std::set<Note*>::iterator it = notes.end()/*notes.find(id)*/;

   if(it == notes.end())
   {
       //si note non existante dans la liste on la charge et si elle n'existe pas on la crée
       //Récupère le type dans le fichier workspace
       QString type = workspace->getType(id);
       QString title;
       Note* n = NULL;

       //On récupère le titre de la note
       QFile fichier(workspace->getPath() + id);
       if(fichier.exists()){
           if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
                //si fichier n'a pu être ouvert, on créer une nouvelle Note
               throw NotesException("Error can't open Note file");
           }

           QTextStream flux(&fichier);
           title = flux.readLine();

           fichier.close();
       } else {
           //Erreur
           throw NotesException("File doesn't exist");
       }

       //On construit la note
       n = noteConstructor(type, id, title);
       n->setWS(workspace->getPath());
       if(n == NULL)
           NotesException("Can't create a note of type: " + type);

       //on ajoute la note
       addNote(n);
       return *n;
    }

    return *(*it);
}

Note& NotesManager::getNewNote(const QString& type, const QString& title){
    Note* n = NULL;
    QString id = getId();

    n = noteConstructor(type, id, (title.isEmpty()) ? QString(type + "_" + id) : title);
    n->setWS(workspace->getPath());
    printf("titleNM = %s\n", n->getTitle().toStdString().c_str());
    if(n == NULL)
        throw NotesException("Can't create a note of type: " + type);

    addNote(n);

    return *n;
}

Note* NotesManager::noteConstructor(const QString& type, const QString& id, const QString& title){
    //Rajouter les types ici ...

    //printf("titleNC = %s\n", title.toStdString().c_str());

    if(type == "Article"){
        return new Article(id, title);
    } else if(type == "Document"){
        return new Document(id, title);
    } else if(type == "Image"){
        return new Image(id, title, QFileDialog::getOpenFileName(NULL, "Selectionner une image", QDir::homePath(), "*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.tiff  *.xbm *.xpm"));
    } else if(type == "Audio"){
        return new Audio(id, title, QFileDialog::getOpenFileName(NULL, "Selectionner un fichier audio", QDir::homePath(), "*.wav"));
    } else if(type == "Video"){
        QString ext = "";
        for(int i = 0; i < QMovie::supportedFormats().size(); i++)
            ext += "*." + QMovie::supportedFormats().at(i) + (i + 1 < QMovie::supportedFormats().size() ? " " : "");
        return new Video(id, title, QFileDialog::getOpenFileName(NULL, "Selectionner une video", QDir::homePath(), ext));
    }

    //type inconnu on laisse à NULL
    return NULL;
}

NoteEditor* NotesManager::noteEdConstructor(Note* n, QWidget *parent){
    //Rajouter les types ici ...

    if(n == NULL)
        return NULL;

    if(n->getType() == "Article"){
        return new ArticleEditor((Article*)n, parent);
    } else if(n->getType() == "Document"){
        return new DocumentEditor((Document*)n, parent);
    } else if(n->getType() == "Image"){
        return new ImageEditor((Image*)n, parent);
    } else if(n->getType() == "Audio"){
        return new AudioEditor((Audio*)n, parent);
    } else if(n->getType() == "Video"){
        return new VideoEditor((Video*)n, parent);
    }

    //type inconnu on laisse à NULL
    return NULL;
}

QIcon NotesManager::getNoteIcon(Note* n){
    //Rajouter les types ici ...

    if(n->getType() == "Article"){
        return ico_article;
    } else if(n->getType() == "Document"){
        return ico_document;
    } else if(n->getType() == "Image"){
        return ico_image;
    } else if(n->getType() == "Audio"){
        return ico_audio;
    } else if(n->getType() == "Video"){
        return ico_video;
    }

    //type inconnu
    return ico_unknown;
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
NotesManager* NotesManager::getInstance(){
    if(!instance) instance=new NotesManager;

    instance->changeWorkspace();
    return instance;
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

    if(workspace)
        delete workspace;
}

void NotesManager::saveNote(Note& n){
    if (n.isModified()) {
        // Création d'un objet QFile
        QFile file(workspace->getPath() + n.getId());

        // On ouvre notre fichier en écriture seule et on vérifie l'ouverture
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            throw NotesException("Erreur sauvegarde d'une note : impossible d'ouvrir un fichier en écriture");

        QTextStream flux(&file);
        flux<<n;
        file.close();
        n.setModified(false);

        QList<QString> tags;

        //met à jour la note dans le workspace (implémenter les tags)
        workspace->addNote(n.getId(), n.getType(), tags);
    }
}

void NotesManager::deleteNote(Note& n){
    removeNote(&n);
    workspace->deleteNote(n.getId());
}

void NotesManager::loadWSNotes(){
    //charger tt les éléments du workspace
    QList<QString> lst_notes = workspace->listNotes();

    if(lst_notes.isEmpty())
        return;

    //Ajout des notes
    for(int i = 0; i < lst_notes.size(); i++)
        //ajout de la note
        instance->getNote(lst_notes.at(i));

    //notes supprimée, restaurées dans la corbeille
    lst_notes = workspace->listNotesD();

    if(lst_notes.isEmpty())
        return;

    //ajout des notes supprimées
    for(int i = 0; i < lst_notes.size(); i++)
        //ajout de la note
        instance->getNote(lst_notes.at(i));
}

void NotesManager::changeWorkspace(){
    //vider la liste de notes en sauvant toutes les notes et le workspace <=> suppression
    instance->reset();

    //chargement de la config
    ConfigManager cm;
    if(cm.getPath().isEmpty())
        return;

    //on ouvre le workspace
    workspace = new Workspace(cm.getPath());
    loadWSNotes();
}
