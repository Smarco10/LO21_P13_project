#include "Image.h"

void Image::load(){
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
         desc += readline();
}

QTextStream& Image::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}
