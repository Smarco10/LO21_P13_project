#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "QHeader.h"
#include "Config.h"
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
    void addNote(Note* n);
    void removeNote(Note* n);

    NotesManager(){}
    ~NotesManager();
    NotesManager(const NotesManager&); // non défini mais privé pour empêcher la duplication
    NotesManager& operator=(const NotesManager&);// même chose
    void reset();

    static Workspace *workspace;
    static void loadWSNotes();

    friend class Document;
    static NotesManager* instance; // pointeur sur l'unique instance
    Note* noteConstructor(const QString& type, const QString& id, const QString& title);
    static QString typeNote(const QString& id);
    static QString getId();

public:
    static NotesManager* getInstance();
    static void libererInstance();

    const QString& getFilename(Note& n){ return n.getId();}

    Note* getNote(unsigned int i = 0);
    Note& getNote(const QString& id);
    Note& getNewNote(const QString& type, const QString& title);
    void saveNote(Note& n);
    void deleteNote(Note& n);
    unsigned int getNbNotes(){ return notes.size();}

    QIcon getNoteIcon(Note* n);
    NoteEditor* noteEdConstructor(Note* n, QWidget *parent=NULL);

    void changeWorkspace();
};

#endif // NOTESMANAGER_H
