﻿#include "Audio.h"

void Audio::load(){
    //récupère les information pouvant manquer
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
     //récupère le chemin du fichier binaire associé
     if(!flux.atEnd())
        path = flux.readLine();
     //récupère la description du fichier
     while(!flux.atEnd())
         desc += flux.readLine();
}

QTextStream& Audio::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getPath()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}

QString Audio::toHTML(){
    return "";
}

QString Audio::toTEX(){
    return "";
}

QString Audio::toTEXT(){
    return "";
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

void AudioEditor::update(QString s){

}

