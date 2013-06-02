#include "Video.h"

void Video::load(){
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

QTextStream& Video::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}

QString Video::toHTML(){
    return "";
}

QString Video::toTEX(){
    return "";
}

QString Video::toTEXT(){
    return "";
}

VideoEditor::VideoEditor(Video *v, QWidget *parent):BinaryEditor(v, parent){
    //A implémenter
}

void VideoEditor::update(QString s){

}
