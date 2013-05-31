#include "Video.h"

void Video::load(){
    //récupère les information pouvant manquer
}

QTextStream& Video::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}
