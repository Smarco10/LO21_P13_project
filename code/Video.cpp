#include "Video.h"

Video::load(){
    //récupère les information pouvant manquer
}

QTextStream& operator<<(QTextStream& f, const Video& v){
    f<<v.getTitle()<<"\n";
    return f;
}
