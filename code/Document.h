#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Note.h"
<<<<<<< HEAD
///\class Document
///Correspond à la spécification de Note pour contenir:
///des sous-notes (Audio, Article, Image, Video)
///un type d'éditeur i.e. un graphisme spécifique
///et des exports HTML,Tex,TEXT correspondants
/*
class Document {
    friend class NotesManager;
    Article** articles;
    unsigned int nbArticles;
    unsigned int nbMaxArticles;
    QString filename;
    QString title;
    bool modified;
    Document(const Document& m);
    Document& operator=(const Document& m);
public:
    Document(const QString& f, const QString& t);
    ~Document() { delete[] articles; }
    const QString& getFilename() const { return filename; }
    const QString& getTitle() const { return title; }
    void setTitle(const QString& t) {modified=true; title=t;}
    unsigned int getNbArticles() const { return nbArticles; }
    Document&  operator<<(Article& a);
    Article& getArticle(unsigned int i);
    const Article& getArticle(unsigned int i) const;
    void removeArticle(unsigned int i);
    void moveArticleUp(unsigned int i);
    void moveArticleDown(unsigned int i);
    bool isModified() const { return modified; }



    class Iterator {
        int nbRemain;
        Article** current;
        friend class Document;
        Iterator(Article** c, int n):nbRemain(n),current(c){}
    public:
        Iterator():nbRemain(0),current(0){}
        bool isDone() const { return nbRemain==0; }
        void next() { if (isDone()) throw NotesException("error, next on an iterator which is done"); nbRemain--; current++; }
        Article& currentItem() const { return **current; }
    };
    Iterator getIterator() { return Iterator(articles,nbArticles); }

    class ConstIterator {
        int nbRemain;
        Article** current;
        friend class Document;
        ConstIterator(Article** c, int n):nbRemain(n),current(c){}
    public:
        ConstIterator():nbRemain(0),current(0){}
        bool isDone() const { return nbRemain==0; }
        void next() { if (isDone()) throw NotesException("error, next on an iterator which is done"); nbRemain--; current++; }
        const Article& currentItem() const { return **current; }
    };
    ConstIterator getIterator() const { return ConstIterator(articles,nbArticles); }
};
//*/
=======
#include "NotesManager.h"
#include "MainWindow.h"

class QListEditor;
class QListEditorItem;
>>>>>>> c6b565c36fe857b07d27aadd946a665ed8f577da

class DocButton:public QPushButton{
    Q_OBJECT
private:
    QWidget *widget;
public:
    DocButton(QWidget* wid, const QIcon& ico, const QString& txt, QWidget *p = NULL):QPushButton(ico, txt, p), widget(wid){}
    DocButton(QWidget* wid, const QString& txt, QWidget *p = NULL):QPushButton(txt, p), widget(wid){}

signals:
    void sendWid(QWidget*);
public slots:
    void getWid();
};

class Document: public Note{
private:
    std::list<Note*> content;
    void operator=(const Document&);
    Document(Document& d);
    void load();
public:
    Document(const QString& id, const QString& title, const std::list<Note*> content = std::list<Note*>()):Note("Document", id, title),content(content){}

    void addSubNote(Note* n);
    void addSubNote(Note *n, unsigned int);
    void removeSubNote(unsigned int);
    void removeSubNote(const Note*);
    Note* getSubNote(unsigned int pos);
    bool isNote(const Note*);
    bool isNote(const QString&);

    unsigned int getNbSubNotes() {return content.size();}
    QTextStream& save(QTextStream& f);
    NoteEditor* getEditor(QWidget *parent = NULL);

    virtual void makehtmlbody(QXmlStreamWriter* qw);
    QString toTEX();
    QString toTEXT();
};

class DocumentEditor: public NoteEditor{
Q_OBJECT
protected:
    std::list<QWidget*> content;
    QDialog *ask;
    QListEditor *notes;

public:
    DocumentEditor(Document* d, QWidget* parent = NULL);
    ~DocumentEditor(){}

    void insertNote(NoteEditor*, QWidget* parent = NULL);

public slots:
    void detachNote(QWidget*);
    void selectNote();
    void openNote(QListEditorItem*);
};

#endif // DOCUMENT_H

