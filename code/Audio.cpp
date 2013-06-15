﻿#include "Audio.h"

void Audio::load(){
    //Si la note est déjà chargée on ne le recharge pas
    if(getLoaded())
        return;

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

     setLoaded(true);
}

QTextStream& Audio::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getPath()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}

QString Audio::toHTML(){

    QXmlStreamWriter* qw=new QXmlStreamWriter;

    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }

    //Creation of the HTML architecture
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
            qw->writeEmptyElement("br");
            qw->writeTextElement("h1",this->getTitle());
            qw->writeEmptyElement("br");
            qw->writeEmptyElement("br");
            qw->writeTextElement("h3",QString("PATH: ")+this->getPath());
            qw->writeEmptyElement("br");
            qw->writeEmptyElement("br");
            qw->writeStartElement("audio");
                qw->writeAttribute("src",this->getPath());
                qw->writeAttribute("controls", "true");
            qw->writeEndElement();
            qw->writeTextElement("p",this->getDesc());
            qw->writeEmptyElement("br");
            //qw->writeTextElement("p",QString("Tag:")+(*it).getTags());
        qw->writeEndElement();
    qw->writeEndElement();
    buffer->close();
    return QString(*file);
}

QString Audio::toTEX(){
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

QString Audio::toTEXT(){
    return getTitle() + "\n\n" + getPath() + "\n\n" + getDesc();
}

AudioEditor::AudioEditor(Audio *a, QWidget *parent):BinaryEditor(a, parent){
    //Ajouter le bouton et la description
    sound = new QSound(a->getPath());

    control = new QWidget;
    controlLay = new QHBoxLayout;

    play_bt = new QPushButton(control->style()->standardIcon(QStyle::SP_MediaPlay), "");
    play_bt->setToolTip("Lecture");

    stop_bt = new QPushButton(control->style()->standardIcon(QStyle::SP_MediaStop), "");
    stop_bt->setToolTip("Stop");

    controlLay->addWidget(play_bt);
    controlLay->addWidget(stop_bt);
    control->setLayout(controlLay);
    zone->layout()->addWidget(control);

    //connecte les play_bt et stop_bt à sound
    QObject::connect(play_bt, SIGNAL(clicked()), sound, SLOT(play()));
    QObject::connect(stop_bt, SIGNAL(clicked()), sound, SLOT(stop()));
}

QString AudioEditor::selectFile(){
    return QFileDialog::getOpenFileName(this, "Selectionner un fichier audio", QDir::homePath(), "*.wav");
}

void AudioEditor::updateBin(){
    if(sound) delete sound;
    sound = new QSound(((Binary*)ressource)->getPath());
}
