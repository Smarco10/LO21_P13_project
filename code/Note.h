#ifndef NOTE_H
#define NOTE_H

#include "QHeader.h"

class Note{
private:
    QString id;
    QString type;

protected:
    QString pathWS;
    QString title;
    bool loaded;
    bool modified;
    bool deleted;
    virtual void load()=0;
    QByteArray* file;
    QBuffer* buffer;
    void createTexHeader(QBuffer*);

public:
    Note(const QString& ty, const QString& i, const QString& tt):id(i),type(ty),title(tt),loaded(false),modified(false){ file =new QByteArray(""); buffer=new QBuffer(file);}

    QString& getId() {return id;}
    QString& getType() {return type;}

    QString& getTitle() {return title;}
    void setTitle(const QString& tt){title = tt; modified = true;}

    void setModified(const bool m){modified = m;}
    bool isModified() const {return modified;}

    void setLoaded(const bool l){loaded = l;}
    bool getLoaded() const {return loaded;}

    QString getWS() const {return pathWS;}
    void setWS(const QString& p="") {pathWS = p;}

    virtual void addSubNote(Note* n);
    virtual void addSubNote(Note* n, unsigned int);
    virtual void removeSubNote(unsigned int);
    virtual Note* getSubNote(unsigned int pos=0);

    bool operator==(const Note* n) const { return this->id == n->id;}
    bool operator<(const Note* n)const{ return this->id < n->id;}
    bool less(const Note* n)const{ return this->id < n->id;}
    virtual QTextStream& save(QTextStream&) = 0;

    QString toHTML();
    virtual void makehtmlbody(QXmlStreamWriter* qw) = 0;
    virtual QString toTEX() = 0;
    virtual QString toTEXT() = 0;

    virtual NoteEditor* getEditor(QWidget* parent = NULL) = 0;
};

QTextStream& operator<<(QTextStream& f, Note& n);

class NoteEditor: public QWidget{
Q_OBJECT
protected:
    QVBoxLayout *mainLay;
    QTabWidget *tabs;
    QScrollArea *area;
    QWidget *zone;
    QVBoxLayout *zoneLayout;

    QLineEdit *title;

    Note* ressource;

public:
    NoteEditor(Note* n, QWidget* parent=0);
    virtual ~NoteEditor(){}

    Note& getRessource() const {return *ressource;}

    QLabel *html;
    QLabel *tex;
    QLabel *text;

public slots:
    void tabed(int);
    void titleMod(QString);
};

#endif


