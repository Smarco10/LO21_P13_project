#include "Audio.h"

void Audio::load(){
    //récupère les information pouvant manquer
    QFile fichier(getId());
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
}

void AudioEditor::update(QString s){

}

