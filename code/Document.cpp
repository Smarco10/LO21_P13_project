﻿#include "Document.h"

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


QTextStream& operator<<(QTextStream& f, const Document& d){
    f<<d.getTitle()<<"\n";
    for(unsigned int i=0; i<d.getNbArticles(); i++){
        f<<d.getArticle(i).getFilename()<<"\n";
    }
    return f;
}

//*/

//*
void Document::addSubNote(Note *n){
    //load();
    content.push_back(n);
    modified = true;
}

void Document::addSubNote(Note *n, unsigned int pos){
    //load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    content.insert(it, n);
    modified = true;
}

void Document::removeSubNote(unsigned int pos){
    //load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    content.erase(it);
    modified = true;
}

Note* Document::getSubNote(unsigned int pos){
    //load();
    std::list<Note*>::iterator it = content.begin();
    for(unsigned int i = 0; i < pos; i++) it++;
    return *it;
}
//*/
