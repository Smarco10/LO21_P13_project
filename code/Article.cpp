#include "Article.h"

/*
Article::Article(const QString& f, const QString& ti, const QString& te):
    filename(f),title(ti),text(te),
    modified(false) // non modifié
{}

void Article::setTitle(const QString& t) {
    modified=true; title=t;
}

void Article::setText(const QString& t) {
    modified=true; text=t;
}

Article::Article(const Article& a):
    title(a.title),filename(a.filename),text(a.text){}

Article& Article::operator=(const Article& a){
    title=a.title; text=a.text; filename=a.filename;
    return *this;
}

QTextStream& operator<<(QTextStream& f, const Article& a){
    f<<a.getTitle()<<"\n";
    f<<a.getText()<<"\n";
    return f;
}
//*/
