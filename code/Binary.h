#ifndef BINARY_H
#define BINARY_H

#include "Note.h"

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

    virtual QString toHTML() = 0;
    virtual QString toTEX() = 0;
    virtual QString toTEXT() = 0;
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

signals:
    virtual void updateS(QString) = 0;

public slots:
    virtual void update(QString s="") = 0;
    void changeFile();
};

#endif // BINARY_H

