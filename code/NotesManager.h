#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "QHeader.h"
#include "Workspace.h"
#include "Note.h"
#include "Article.h"
#include "Document.h"
#include "Audio.h"
#include "Image.h"
#include "Video.h"

class NotesManager {
private:
    std::set<Note*> notes;
    unsigned int getNbNotes(){ return notes.size();}
    //coder operateur < > pour le find;
    void addNote(Note* n);
    void removeNote(Note* n);

    NotesManager(){}
    ~NotesManager();
    NotesManager(const NotesManager&); // non défini mais privé pour empêcher la duplication
    NotesManager& operator=(const NotesManager&);// même chose
    void reset();

    static Workspace *workspace;
    static void loadWSNotes();
    static void changeWorkSpace(const QString& path = ".");

    friend class Document;
    static NotesManager* instance; // pointeur sur l'unique instance
    Note* noteConstructor(const QString& type, const QString& id, const QString& title);
    static QString typeNote(const QString& id);
    static QString getId();

public:
    static NotesManager& getInstance();
    static void libererInstance();

    const QString& getFilename(Note& n){ return n.getId();}

    Note& getNote(QString& id);
    Note& getNewNote(const QString& type, const QString& title);
    void saveNote(Note& n);
    void deleteNote(Note& n);
};

#endif // NOTESMANAGER_H
