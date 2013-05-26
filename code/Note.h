#ifndef NOTE_H
#define NOTE_H

#include "QHeader.h"

class Note
{
    unsigned int id;

protected:
    QString title;
    bool loaded;
    bool modified;
    //virtual void load()=0;

public:
    Note(unsigned int i, const QString& tt):id(i),title(tt),loaded(false),modified(false){}

    bool getId() const {return id;}

    QString& getTitle() {return title;}
    void setTitle(const QString& tt){title = tt;}

    void setModified(const bool m){modified = m;}
    bool isModified() const {return modified;}

    void setLoaded(const bool l){loaded = l;}
    bool getLoaded() const {return loaded;}

    virtual void addSubNote(Note* n);
    virtual void addSubNote(Note* n, unsigned int);
    virtual void removeSubNote(unsigned int);
    virtual Note* getSubNote(unsigned int pos=0);

    //Iterator begin() const;
    //Iterator end() const;
};

#endif


