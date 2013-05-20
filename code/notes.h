#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>

using namespace std;

int strcmp(const string&, const string&);

namespace Frame{
    class Article{
    private:
		bool modified;
        string filename;
        string title;
        string text;
        string tags;
        unsigned int id;

    public:
        Article(const string& fn, const string& tt, const string& txt, const string& tgs=""):modified(true),filename(fn),title(tt),text(txt),tags(tgs){time_t t; time(&t); id = t;};

		bool getModified(){return this->modified;}
        string getFilename(){return this->filename;}
        string getTitle(){return this->title;}
        string getText(){return this->text;}
        unsigned int getId(){return id;}
        string getTags(){return tags;}

		void setModified(bool modified){this->modified = modified;}
        void setTitle(const string& title){this->title = title; this->modified = true;};
        void setText(const string& text){this->text = text; this->modified = true;};

        bool hasTag(string tag){return (tags.find(tag, 0) < tags.npos);}
        void addTag(string tag){if(!hasTag(tag)) tags += tag + "/";}

    private:
        Article(const Article&);
        Article& operator=(const Article&);
    };

    //Class qui gère les exceptions
    class NotesException{
    public:
        NotesException(const string& message):info(message){}
        string getInfo() const { return info; }

    private:
        string info;
    };

    class Document{
    private:
		bool modified;
        unsigned int nbMaxArticles;
        unsigned int nbArticles;
        string filename;
        string title;
        Article** articles;

    public:
        Document(const string& fn, const string& tt):modified(true),nbMaxArticles(10),nbArticles(0),filename(fn),title(tt){
        	this->articles = new Article*[this->nbMaxArticles];};
        ~Document();

        bool getModified(){return this->modified;}
		unsigned int getNbArticles(){return this->nbArticles;}
        string getFilename(){return this->filename;}
        string getTitle(){return this->title;}

        void setModified(bool modified){this->modified = modified;}
        void setTitle(const string& title){this->title = title; this->modified = true;}

        Document& operator<<(Article&);

        Article& getArticle(unsigned int position){return *this->articles[position];}
        const Article& getArticle(unsigned int position)const{return *this->articles[position];}

        void removeArticle(unsigned int position);

        void moveArticleUp(unsigned int position);
        void moveArticleDown(unsigned int position);

        class Iterator{
        private:
            Article** current;
            friend class Document;
            Iterator(Article** arts){current = arts;}

        public:
            Iterator():current(NULL){}

            Article& getCurrent() const {return **current;}

            bool operator!=(Iterator it){return (this->current != it.current);}

            Iterator& operator++(){
                this->current ++;
                return *this;}

            Article& operator*(){return **current;}
        };

        Iterator begin(){return Iterator(articles);};
        Iterator end(){return Iterator(articles + nbArticles);};

        class ConstIterator{
        private:
            unsigned int nbRemain;
            Article** current;
            friend class Document;
            ConstIterator(Article** arts, unsigned int nbR){current = arts; nbRemain = nbR;}

        public:
            ConstIterator():nbRemain(0),current(NULL){}
            bool isDone() const {return (nbRemain == 0);}
            void next(){
                if(!isDone()){
                    nbRemain --;
                    current ++;
                }
            }
            const Article& getCurrent() const {return **current;}
        };

        ConstIterator getIterator() const {return ConstIterator(articles, nbArticles);}

    private:
        Document(const Document&);
        Document& operator=(const Document&);
    };

    class NotesManager {
    private:
        Article** articles;
        Document** documents;
        unsigned int nbArticles;
        unsigned int nbMaxArticles;
        unsigned int nbDocuments;
        unsigned int nbMaxDocuments;
        void addArticle(Article* a);
        void addDocument(Document *d);

        /*Utilisé pour le singleton*/
        static NotesManager* instanceUnique;

        NotesManager():nbArticles(0),nbMaxArticles(10),nbDocuments(0),nbMaxDocuments(10){
        	this->articles = new Article*[this->nbMaxArticles];
        	this->documents = new Document*[this->nbMaxDocuments];}
        NotesManager(const NotesManager& mng);
        NotesManager& operator=(const NotesManager& mng);
        ~NotesManager();

    public:
        static NotesManager& getInstance();
        static void delInstance();

        Article& getNewArticle(const string&);
        Document& getNewDocument(const string&);

        Article& getArticle(const string&);
        Article& getArticle(Article&);

        Document& getDocument(const string&);
        Document& getDocument(Document&);

        void saveArticle(Article&);
        void saveDocument(Document&);

        /*Dans le notemanager faire un enum Type {Document, Article} pour savoir si l'on est en train de parcourir un tableau d'article ou un tableau de document
        utilisé par getIterator()*/

        enum Type {document, article};

		class Iterator{
        private:
            unsigned int nbRemain;
            Article** currentA;
            Document** currentD;
            Type t;

            friend class NotesManager;
            Iterator(Article** arts, unsigned int nbR){t = article; currentA = arts; nbRemain = nbR;}
            Iterator(Document** docs, unsigned int nbR){t = document; currentD = docs; nbRemain = nbR;}

        public:
            Iterator():nbRemain(0),currentA(NULL),currentD(NULL){}
            bool isDone() const {return (nbRemain == 0);}
            void next(){
                if(!isDone()){
                    nbRemain --;
                    if(t == article) currentA ++; else currentD ++;
                }
            }

            Article& currentArticle() const {return **currentA;}
            Document& currentDocument() const {return **currentD;}
        };

        Iterator getIterator(Type type) const {
        	switch(type){
			case article:
				return Iterator(articles, nbArticles);
				break;
			case document:
				return Iterator(documents, nbDocuments);
				break;
			}
			return Iterator();
        }
    };
}

#endif // NOTES_H_INCLUDED
