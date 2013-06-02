#ifndef NOTE_H
#define NOTE_H

#include "QHeader.h"

class Note
{
    QString id;

protected:
    QString title;
    bool loaded;
    bool modified;
    virtual void load()=0;

public:
    Note(const QString& i, const QString& tt):id(i),title(tt),loaded(false),modified(false){}

    QString& getId() {return id;}

    QString& getTitle() {return title;}
    void setTitle(const QString& tt){title = tt; modified = true;}

    void setModified(const bool m){modified = m;}
    bool isModified() const {return modified;}

    void setLoaded(const bool l){loaded = l;}
    bool getLoaded() const {return loaded;}

    virtual void addSubNote(Note* n);
    virtual void addSubNote(Note* n, unsigned int);
    virtual void removeSubNote(unsigned int);
    virtual Note* getSubNote(unsigned int pos=0);

    bool operator<(const Note& n)const{ return this->id < n.id;}
    virtual QTextStream& save(QTextStream&) = 0;

    virtual QString toHTML() = 0;
    virtual QString toTEX() = 0;
    virtual QString toTEXT() = 0;
};

QTextStream& operator<<(QTextStream& f, Note& n);

class NoteEditor: public QWidget{
Q_OBJECT
protected:
    QTabWidget *tabs;
    QScrollArea *area;
    QWidget *zone;
    QVBoxLayout *zoneLayout;

    QLineEdit *title;

    Note* ressource;

public:
    NoteEditor(Note* n, QWidget* parent=0);
    virtual ~NoteEditor(){}

    QLabel *html;
    QLabel *tex;
    QLabel *text;

signals:
    virtual void updateS(QString);

public slots:
    void modified();
    void modified(QString);
    virtual void update(QString s="") = 0;
};

#endif


