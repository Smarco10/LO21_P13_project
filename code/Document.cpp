#include "Document.h"
#include "NotesManager.h"

/*
Document::Document(const QString& f, const QString& t):
    filename(f),title(t),
    modified(false), // non modifié
    articles(0),nbArticles(0),nbMaxArticles(0) // initialement, aucun article
{}

Document& Document::operator<<(Article& a){
    if (nbArticles==nbMaxArticles){
        // il faut agrandir le tableau
        Article** newArticles= new Article*[nbMaxArticles+5];
        for(unsigned int i=0; i<nbArticles; i++) newArticles[i]=articles[i];
        Article** oldArticles=articles;
        articles=newArticles;
        nbMaxArticles+=5;
        if (oldArticles) delete[] oldArticles;
    }
    articles[nbArticles++]=&a;
    modified=true;
    return *this;
}

void Document::removeArticle(unsigned int i){
    if (i<nbArticles){
        for(unsigned int j=i; j<nbArticles-1; j++) articles[j]=articles[j+1];
        modified=true;
    }else throw NotesException("error, removing an article");
}

void Document::moveArticleUp(unsigned int i){
    if (i<nbArticles && i>0){
        Article* a=articles[i];
        articles[i]=articles[i-1];
        articles[i-1]=a;
        modified=true;
    }else throw NotesException("error, moving up an article");
}

void Document::moveArticleDown(unsigned int i){
    if (i>=0 && i<nbArticles-1){
        Article* a=articles[i];
        articles[i]=articles[i+1];
        articles[i+1]=a;
        modified=true;
    }else throw NotesException("error, moving down an article");
}

Article& Document::getArticle(unsigned int i){
    if (i>=0 && i<nbArticles){
        return *articles[i];
    }else throw NotesException("error, this article does not exists");
}

const Article& Document::getArticle(unsigned int i) const {
    if (i>=0 && i<nbArticles){
        return *articles[i];
    }else throw NotesException("error, this article does not exists");
}

Document::Document(const Document& m):
    articles(new Article*[m.nbArticles]),
    nbArticles(m.nbArticles),
    nbMaxArticles(m.nbArticles),
    filename(m.filename),title(m.title){
        for(unsigned int i=0; i<nbArticles; i++)
            articles[i]=m.articles[i];
}

Document& Document::operator=(const Document& m){
    if (this!=&m){
        filename=m.filename;
        title=m.title;
        Article** newarticles=new Article*[m.nbArticles];
        for(unsigned int i=0; i<nbArticles; i++)
            newarticles[i]=m.articles[i];
        Article** old=articles;
        articles=newarticles;
        delete[] old;
    }
    return *this;
}
//*/

//*
void Document::addSubNote(Note *n){
    load();
    content.push_back(n);
    modified = true;
}

void Document::addSubNote(Note *n, unsigned int pos){
    load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    content.insert(it, n);
    modified = true;
}

void Document::removeSubNote(unsigned int pos){
    load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    content.erase(it);
    modified = true;
}

Note* Document::getSubNote(unsigned int pos){
    load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    return *it;
}

void Document::load(){
    //récupère les information pouvant manquer comme la liste des notes
    //Vérifie si on a besoin d'annalyser le fichier (liste pleine)
    if(content.size() > 0)
        return;

    QFile fichier(getId());
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
        throw NotesException("Can't open document file");
    }

     QTextStream flux(&fichier);
     //saute la première ligne
     flux.readLine();
     while(!flux.atEnd()){
         //Pour chaques ligne, enregistre la note et l'ajoute au document
          QString subfile = flux.readLine();
          //vérifie que le fichier n'est pas déjà dans la liste
          for(std::list<Note*>::iterator it = content.begin(); it != content.end(); it++)
              if((*it)->getId() == subfile)
                  //passe au fichier suivant
                  continue;

          //si fichier non présent dans la liste
          //création d'une note en mémoire, catcher les exceptions
          Note& note = NotesManager::instance->getNote(subfile);

          //ajoute le fichier à la listte
          addSubNote(&note);
     }
}

QTextStream& Document::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    for(unsigned int i=0; i<this->getNbSubNotes(); i++){
        f<<(this->getSubNote(i))->getId()<<"\n";
    }
    return f;
}
//*/
