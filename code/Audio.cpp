#include "Audio.h"

void Audio::load(){
    //récupère les information pouvant manquer
}

QTextStream& Audio::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}
