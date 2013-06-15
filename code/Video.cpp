﻿#include "Video.h"

void Video::load(){
    //récupère les information pouvant manquer
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
     //récupère le chemin du fichier binaire associé
     if(!flux.atEnd())
        path = flux.readLine();
     //récupère la description du fichier
     while(!flux.atEnd())
         desc += flux.readLine();
}

QTextStream& Video::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getPath()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}

QString Video::toTEX(){
    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
         throw NotesException("Buffer unavailable for HTML export.");
     }
    createTexHeader(buffer);
    buffer->write("\\begin{document}\n");
    buffer->write(("\\chapter{"+this->getTitle()+"}\n").toAscii());
    buffer->write(("{\Large ID:"+this->getId()+"}\n").toAscii());
    buffer->write(("\\paragraph{PATH:"+this->getPath()+"}"+this->getDesc()+"\n").toAscii());
    buffer->write("\\end{document}");
    buffer->close();
    return QString(*file);
}

QString Video::toHTML(){
    QXmlStreamWriter *qw =  new QXmlStreamWriter;
    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }
    createHtmlTree(buffer);
    qw->writeEmptyElement("br");
    qw->writeTextElement("h1",QString("Titre:")+this->getTitle());
    qw->writeTextElement("h2",QString("ID:")+this->getId());
    qw->writeTextElement("h3",QString("PATH:")+this->getPath());
    qw->writeStartElement("video controls ");
    qw->writeAttribute("src",this->getPath());
    qw->writeEndElement();
    qw->writeTextElement("p",this->getDesc());
    //qw->writeTextElement("p",QString("Tag:")+(*it).getTags());
    qw->writeEmptyElement("br");

    endHtmlTree(buffer);
    buffer->close();
    return QString(*file);
}

QString Video::toTEXT(){
    return "";
}

VideoEditor::VideoEditor(Video *v, QWidget *parent):BinaryEditor(v, parent){
    control = new QWidget(parent);
    controlLay = new QHBoxLayout;

    movie = new QMovie(path);
    frame = new QLabel(parent);
    frame->setMovie(movie);

    zone->layout()->addWidget(frame);

    //changer le nom du bouton et le passer à pause quand la lecture est lancée
    play_bt = new QPushButton(control->style()->standardIcon(QStyle::SP_MediaPlay), "");
    play_bt->setToolTip("Lecture");

    pause_bt = new QPushButton(control->style()->standardIcon(QStyle::SP_MediaPause), "");
    pause_bt->setToolTip("Pause = Lecture (non fonctionnel)");

    stop_bt = new QPushButton(control->style()->standardIcon(QStyle::SP_MediaStop), "");
    stop_bt->setToolTip("Stop");

    controlLay->addWidget(play_bt);
    controlLay->addWidget(stop_bt);
    control->setLayout(controlLay);
    zone->layout()->addWidget(control);

    //permettre de faire varier la vitesse de leture etc.
    //permettre de réer une note image à partir de l'image courrante (en plus)

    //connecter play_bt, pause_bt et stop_bt à movie
    QObject::connect(play_bt, SIGNAL(clicked()), movie, SLOT(start()));
    QObject::connect(pause_bt, SIGNAL(clicked(bool)), movie, SLOT(setPaused(bool)));
    QObject::connect(stop_bt, SIGNAL(clicked()), movie, SLOT(stop()));
}

void VideoEditor::update(QString s){

}
