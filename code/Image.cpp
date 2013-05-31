#include "Image.h"

Image::load(){
    //récupère les information pouvant manquer
}

QTextStream& operator<<(QTextStream& f, const Image& i){
    f<<i.getTitle()<<"\n";
    return f;
}
