#include "Article.h"
#include<QDomElement>
#include<QDomDocument>
void Article::load(){
    //récupère les information pouvant manquer comme le contenu
    QFile fichier(getId());
    //on sort si le fichier n'existe pas
    if(!fichier.exists())
        return;

    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
        throw NotesException("Can't open document file");
    }

     QTextStream flux(&fichier);
     //saute la première ligne
     flux.readLine();
     //récupère tout le contenu
     while(!flux.atEnd())
        content += flux.readLine();
}

QTextStream& Article::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getContent()<<"\n";
    return f;
}

QString Article::toHTML(){



}

QString Article::toTEX(){
    return "";
}

QString Article::toTEXT(){
    return "";
}

ArticleEditor::ArticleEditor(Article* a, QWidget* parent):NoteEditor(a, parent){
    content = new QTextEdit(this);

    content->setText(a->getContent());

    zone->layout()->addWidget(content);
}

void ArticleEditor::update(QString s){

}


