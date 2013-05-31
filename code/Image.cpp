#include "Image.h"

void Image::load(){
    //récupère les information pouvant manquer
}

QTextStream& Image::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}
