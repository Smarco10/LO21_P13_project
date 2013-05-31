#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Note.h"

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

class Document: public Note{
private:
    std::list<Note*> content;
    void operator=(const Document&);
    Document(const Document& d):Note(0, d.title),content(d.content){}
    void load();
public:
    Document(const QString& id, const QString& title, const std::list<Note*> content = std::list<Note*>()):Note(id, title),content(content){}

    void addSubNote(Note* n);
    void addSubNote(Note *n, unsigned int);
    void removeSubNote(unsigned int);
    Note* getSubNote(unsigned int pos);

    unsigned int getNbSubNotes() {return content.size();}
    QTextStream& save(QTextStream& f);
};

#endif // DOCUMENT_H

