#ifndef ARTICLE_H
#define ARTICLE_H

#include "QHeader.h"

QTextStream& operator<<(QTextStream& f, const Article& a);

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

#endif // ARTICLE_H
