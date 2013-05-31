#ifndef ARTICLE_H
#define ARTICLE_H

#include "Note.h"

/*
class Article {
	friend class NotesManager;
    QString filename;
    QString title;
    QString text;
	bool modified;
	Article(const Article&);
	Article& operator=(const Article&);
public:
    Article(const QString& f, const QString& ti, const QString& te);
    const QString& getFilename() const { return filename; }
    const QString& getTitle() const { return title; }
    const QString& getText() const { return text; }
    void setTitle(const QString& t);
    void setText(const QString& t);
	bool isModified() const { return modified; }
};
//*/

class Article: public Note{
    QString content;
    void operator=(const Article& a);
    Article(const Article& a):Note(0, a.title), content(a.content){}
    void load();
public:
    Article(const QString& id, const QString& title, const QString& ctt=""):Note(id, title), content(ctt){}

    QString getContent(){load();
        return content;}

    void setContent(const QString& ctt){load();
        content = ctt;
        modified = true;}

    QTextStream& save(QTextStream& f);
};

#endif // ARTICLE_H
