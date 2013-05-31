#ifndef BINARY_H
#define BINARY_H

#include "Note.h"

class Binary: public Note{
    QString desc;
    QString path;
    Binary(const Binary& b):Note(0, b.title), desc(b.desc),path(b.path){}
    void operator=(const Binary& b);
    //void load();

public:
    Binary(const QString& id, const QString& title, const QString& d="", const QString& p=""):Note(id, title), desc(d),path(p){}

    QString& getDesc() {//load();
        return desc;}
    void setDesc(const QString& d){//load();
        desc = d;
        modified = true;}

    QString& getPath() {//load();
        return path;}
    void setPath(const QString& p){//load();
        path = p;
        modified = true;}
};

#endif // BINARY_H

