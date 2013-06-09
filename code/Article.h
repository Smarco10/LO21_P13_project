#ifndef ARTICLE_H
#define ARTICLE_H

#include "Note.h"

class Article: public Note{
    QString content;
    void operator=(const Article& a);
    Article(Article& a);
    void load();
public:
    Article(const QString& id, const QString& title, const QString& ctt=""):Note("Article", id, title), content(ctt){printf("titleA = %s\n", title.toStdString().c_str());}

    QString getContent(){load();
        return content;}

    void setContent(const QString& ctt){load();
        content = ctt;
        modified = true;}

    QString toHTML();
    QString toTEX();
    QString toTEXT();

    QTextStream& save(QTextStream& f);
};

class ArticleEditor: public NoteEditor{
Q_OBJECT
protected:
    QTextEdit *content;

public:
    ArticleEditor(Article* a, QWidget* parent=0);
    ~ArticleEditor(){}

signals:
    void updateS(QString);

public slots:
    void update(QString s="");
};

#endif // ARTICLE_H
