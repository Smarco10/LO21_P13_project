﻿#include "Article.h"
<<<<<<< HEAD
#include<QDomElement>
#include<QDomDocument>
#include<algorithm>
=======

>>>>>>> 9c6bb3b2bfe54891bfec9d4cead12caeb6b1f349
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
<<<<<<< HEAD

    QXmlStreamWriter* qw=new QXmlStreamWriter;


   if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }
    createHtmlTree(buffer);
    qw->writeTextElement("h1",QString("Titre:")+this->getTitle());
    qw->writeTextElement("h2",QString("ID:")+this->getId());
    qw->writeTextElement("p",this->getContent());
    //qw->writeTextElement("p",QString("Tag:")+this->getTags());
    endHtmlTree(buffer);
    buffer->close;
    return QString(*file);


=======
    return "";
>>>>>>> 9c6bb3b2bfe54891bfec9d4cead12caeb6b1f349
}

QString Article::toTEX(){
    return "";
}

QString Article::toTEXT(){
    return "";
}

ArticleEditor::ArticleEditor(Article* a, QWidget* parent):NoteEditor(a, parent){
    content = new QTextEdit;
    content->setText(a->getContent());

    zone->layout()->addWidget(content);
}

void ArticleEditor::update(QString s){

}


