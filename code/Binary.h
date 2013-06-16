#ifndef BINARY_H
#define BINARY_H

#include "Note.h"
///\class Binary (abstraite)
///Correspond à la spécification de Note pour contenir:
///un fichier binaire
///une description
///un Path( chemin d'accès)
///un type d'éditeur i.e. un graphisme spécifique
///

class Binary: public Note{
protected:
    QString desc;
    QString path;
    Binary(Binary& b);
    void operator=(const Binary& b);
    virtual void load() = 0;

public:
    Binary(const QString& type, const QString& id, const QString& title, const QString& d, const QString& p):Note(type, id, title), desc(d),path(p){}

    QString& getDesc() {load();
        return desc;}
    void setDesc(const QString& d){load();
        desc = d;
        modified = true;}

    QString& getPath() {load();
        return path;}
    void setPath(const QString& p){load();
        path = p;
        modified = true;}

    virtual QTextStream& save(QTextStream& f) = 0;
    virtual NoteEditor* getEditor(QWidget* parent = NULL) = 0;

    virtual QString toTEX() = 0;
    virtual QString toTEXT() = 0;
    virtual void makehtmlbody(QXmlStreamWriter *qw);
};

class BinaryEditor: public NoteEditor{
Q_OBJECT
protected:
    QTextEdit *desc;
    QWidget *pathZone;
    QPushButton *chPath;
    QLabel *path;
    QHBoxLayout *pathLay;

public:
    BinaryEditor(Binary* b, QWidget* parent=0);
    virtual ~BinaryEditor(){}
    virtual QString selectFile() = 0;
    virtual void updateBin() = 0;

public slots:
    void changeFile();
    void descMod();
};

#endif // BINARY_H

