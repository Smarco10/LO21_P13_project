#ifndef NOTESMANAGER_H
#define NOTESMANAGER_H

#include "QHeader.h"
#include "Note.h"

class NotesManager {
private:
    std::set<Note> notes ;
    unsigned int getNbNotes(){ return notes.size;}
    //coder operateur < > pour le find;

    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager&); // non défini mais privé pour empêcher la duplication
    NotesManager& operator=(const NotesManager&);// même chose
    static NotesManager* instance; // pointeur sur l'unique instance
public:
    static NotesManager& getInstance();
    static void libererInstance();

    Note& getNote(const unsigned int id);
    Note& getNewNote(const QString& filename);
    void saveNote(Note& n);

    enum typeElement { article, document};

};


#endif // NOTESMANAGER_H
