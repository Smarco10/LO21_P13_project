#include "Article.h"

void Article::load(){
    //récupère les information pouvant manquer comme le contenu
    QFile fichier(getId());
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
