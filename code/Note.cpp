#include "Note.h"

void Note::addSubNote(Note *n){throw NotesException("Bad using");}
void Note::addSubNote(Note *n, unsigned int pos){throw NotesException("Bad using");}
Note* Note::getSubNote(unsigned int pos){throw NotesException("Bad using");}
void Note::removeSubNote(unsigned int pos){throw NotesException("Bad using");}

QTextStream& operator<<(QTextStream& f, Note& n){
    return n.save(f);
}

