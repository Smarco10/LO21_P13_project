#include "Audio.h"

Audio::load(){
    //récupère les information pouvant manquer
}

QTextStream& operator<<(QTextStream& f, const Audio& a){
    f<<a.getTitle()<<"\n";
    return f;
}
