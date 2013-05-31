#include "Article.h"

void Article::load(){
    //récupère les information pouvant manquer comme le contenu
}

QTextStream& Article::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getContent()<<"\n";
    return f;
}
