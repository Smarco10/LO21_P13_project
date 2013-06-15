﻿#include "Article.h"

void Article::load(){
    //Si la note est déjà chargée on ne le recharge pas

    if(getLoaded())
        return;

    //récupère les information pouvant manquer comme le contenu
    QFile fichier(getWS() + getId());
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

    setLoaded(true);
}

QTextStream& Article::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getContent()<<"\n";
    return f;
}

QString Article::toHTML(){
    QXmlStreamWriter* qw=new QXmlStreamWriter;

   if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }

   qw->setDevice(buffer);
   qw->setAutoFormatting(true);
   qw->setAutoFormattingIndent(-1);
   qw->writeDTD("<!DOCTYPE html>");
   qw->writeStartElement("html");
       qw->writeStartElement("head");
           qw->writeEmptyElement("meta");
           qw->writeAttribute("charset","utf-8");
           qw->writeTextElement("title",this->getTitle());
       qw->writeEndElement();
       qw->writeStartElement("body");
            qw->writeTextElement("h1",this->getTitle());
            qw->writeEmptyElement("br");
            qw->writeEmptyElement("br");
            qw->writeTextElement("p",this->getContent());
            qw->writeEmptyElement("br");
            //qw->writeTextElement("p",QString("Tag:")+this->getTags());
        qw->writeEndElement();
    qw->writeEndElement();
    buffer->close();
    return QString(*file);
}


QString Article::toTEX(){

    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
         throw NotesException("Buffer unavailable for HTML export.");
     }
    createTexHeader(buffer);
    buffer->write("\\begin{document}\n");
    buffer->write((QString("\\chapter{")+this->getTitle()+QString("}\n")).toAscii());
    buffer->write((QString("\\paragraph{}")+this->getContent()).toAscii());
    buffer->write("\\end{document}");
    buffer->close();

    return QString(*file);
}

QString Article::toTEXT(){
    return this->getTitle() + "\n\nContenu de l'article: " + this->getContent();
}

ArticleEditor::ArticleEditor(Article* a, QWidget* parent):NoteEditor(a, parent){
    content = new QTextEdit;
    content->setText(a->getContent());

    zone->layout()->addWidget(content);

    QObject::connect(content, SIGNAL(textChanged()), this, SLOT(contentMod()));
}

void ArticleEditor::contentMod(){
    ((Article*)ressource)->setContent(content->toPlainText());
}

void ArticleEditor::update(QString s){

}


