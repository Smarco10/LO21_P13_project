#include "Article.h"

Article::load(){
    //récupère les information pouvant manquer commen le contenu
}

QTextStream& operator<<(QTextStream& f, const Article& a){
    f<<a.getTitle()<<"\n";
    f<<a.getText()<<"\n";
    return f;
}
