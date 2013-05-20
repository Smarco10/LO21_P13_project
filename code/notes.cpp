#include "notes.h"

int strcmp(const string& str1, const string& str2){
	return std::strcmp(str1.c_str(), str2.c_str());
}

namespace Frame{
    /*Permet d'initialiser le singleton du NotesNanager*/
    NotesManager* NotesManager::instanceUnique = 0;

    NotesManager& NotesManager::getInstance(){
        if(instanceUnique == NULL){
            instanceUnique = new NotesManager;
        }
        return *instanceUnique;
    }

    void NotesManager::delInstance(){
        if(instanceUnique != NULL){
            delete instanceUnique;
            instanceUnique = NULL;
        }
    }

    Article& NotesManager::getNewArticle(const string& filename){
        Article *art = new Article(filename, "", "");
        addArticle(art);
        return *art;
    }

    Document& NotesManager::getNewDocument(const string& filename){
        Document *doc = new Document(filename, "");
        addDocument(doc);
        return *doc;
    }

    Article& NotesManager::getArticle(const string& filename){
    	Article *article = NULL;

		//recherche si l'article est déjà en mémoire
		for(unsigned int i = 0; i < this->nbArticles; i++)
			if(strcmp(filename, this->articles[i]->getFilename()) == 0){
				article = this->articles[i];
				break;
			}

		if(article == NULL){
			ifstream file(filename.c_str()); // open file

			if (!file)
				throw NotesException("getArticle(): Error: opening a file");

			char tmp[256];
			file.getline(tmp,256); // get title on the first line
			string title = tmp;

			string text; // build text
			while (file.good()){
				char c = file.get(); // get character from file
				if (file.good())
					text += c; // add it to the text
			}

			file.close(); // close file

			article = &getNewArticle(filename);
			article->setTitle(title);
			article->setText(text);
		}

		return *article;
    }

	Document& NotesManager::getDocument(const string& filename){
		Document *document = NULL;

		//recherche si le document est déjà en mémoire
		for(unsigned int i = 0; i < this->nbDocuments; i++)
			if(strcmp(filename, this->documents[i]->getFilename()) == 0)
				document = this->documents[i];

		if(document == NULL){
			ifstream file(filename.c_str()); // open file

			if (!file)
				throw NotesException("getDocument(): Error: opening a file");

			char tmp[256];
			file.getline(tmp, sizeof(tmp)); // get title on the first line
			string title = tmp;

			document = &getNewDocument(filename); // Create a new Document ref.
			document->setTitle(title);

			char articleFilename[256]; // build text
			while (file.good()){
				file.getline(articleFilename, sizeof(articleFilename)); // get character from file
				*document << getArticle(articleFilename); //add new article in document structure
			}

			file.close(); // close file
		}

		return *document;
	}

	Article& NotesManager::getArticle(Article& art){
	    //récupère le basename et ajoute _copy et l'extension
        string filename = art.getFilename();
        filename.insert(filename.find_last_of("."), "_copy");
		Article& article = this->getNewArticle(filename);

        article.setTitle(art.getTitle());
        article.setText(art.getText());

		return article;
	}

	Document& NotesManager::getDocument(Document& doc){
	    //récupère le basename et ajoute Copy et l'extension
        string filename = doc.getFilename();
        filename.insert(filename.find_last_of("."), "_copy");
		Document& document = this->getNewDocument(filename);

        document.setTitle(doc.getTitle());

		return document;
	}

    void NotesManager::addArticle(Article* a){
        if(this->nbArticles >= this->nbMaxArticles){
            //réallouer de la mémoire à nbMaxArticles
            this->nbMaxArticles += 5;
            Article **articlesBuff = new Article*[this->nbMaxArticles];

            for(unsigned int i = 0; i < this->nbArticles; i++)
                articlesBuff[i] = this->articles[i];

            delete[] this->articles;
            this->articles = articlesBuff;
        }

        this->articles[this->nbArticles] = a;

        this->nbArticles ++;
    }

    void NotesManager::addDocument(Document* a){
        if(this->nbDocuments >= this->nbMaxDocuments){
            //réallouer de la mémoire à nbMaxArticles
            this->nbMaxDocuments += 2;
            Document **documentsBuff = new Document*[this->nbMaxDocuments];

            for(unsigned int i = 0; i < this->nbDocuments; i++)
                documentsBuff[i] = this->documents[i];

            delete[] this->documents;
            this->documents = documentsBuff;
        }

        this->documents[this->nbDocuments] = a;

        this->nbDocuments ++;
    }

    void NotesManager::saveArticle(Article& article){
		if(article.getModified()){
			ofstream file(article.getFilename().c_str(), ios::trunc); //open file and discard it

			if(!file)
				throw NotesException("saveArticle(): Error: opening a file");

			file << article.getTitle();
			file << "\n" << article.getText();

			file.close();
			article.setModified(false);
		}
    }

	void NotesManager::saveDocument(Document& document){
		if(document.getModified()){
			ofstream file(document.getFilename().c_str(), ios::trunc); //open file and discard it

			if(!file)
				throw NotesException("saveDocument(): Error: opening a file");

			file << document.getTitle();

			for(unsigned int i = 0; i < document.getNbArticles(); i++){
				saveArticle(document.getArticle(i));
				file << "\n" << document.getArticle(i).getFilename();
			}

			file.close();
			document.setModified(false);
		}
	}

    NotesManager::~NotesManager(){
    	//Sauvegarde et suppression du tableau de documents (mais pas leurs articles (ils sont juste sauvegardés))
		for(unsigned int i = 0; i < this->nbDocuments; i++)
            if(this->documents[i] != NULL){
            	saveDocument(*this->documents[i]);
				delete this->documents[i];
				this->documents[i] = NULL;
			}

		if(this->documents != NULL){
			delete[] this->documents;
			this->documents = NULL;
		}

    	//Sauvegarde et suppression du tableau d'articles
        for(unsigned int i = 0; i < this->nbArticles; i++){
			if(this->articles[i] != NULL){
				saveArticle(*this->articles[i]);
				delete this->articles[i];
				this->articles[i] = NULL;
			}
        }

		if(this->articles != NULL){
			delete[] this->articles;
			this->articles = NULL;
		}
    }

    Document& Document::operator<<(Article& article){
        //Vérification que article n'existe pas déjà dans doc sinon on sort sans rien faire
		for(unsigned int i = 0; i < this->nbArticles; i++)
			if(strcmp(this->articles[i]->getFilename(), article.getFilename()) == 0)
				return *this;

        //ajoute un article en dernière position
        if(this->nbArticles >= this->nbMaxArticles){
            //réallouer de la mémoire à nbMaxArticles
            this->nbMaxArticles += 5;
            Article **articlesBuff = new Article*[this->nbMaxArticles];

            for(unsigned int i = 0; i < this->nbArticles; i++)
                articlesBuff[i] = this->articles[i];

            delete[] this->articles;
            this->articles = articlesBuff;
        }

        this->articles[this->nbArticles] = &article;
        this->nbArticles++;

        this->setModified(true);

        return *this;
    }

    void Document::removeArticle(unsigned int position){
    	if(position < this->nbArticles && this->articles[position] != NULL)
			return;

        delete this->articles[position];
        this->articles[position] = NULL;

        for(unsigned int i = position; i < this->nbArticles - 1; i ++)
            this->moveArticleUp(i + 1);

        this->nbArticles --;
        this->setModified(true);
    }

    void Document::moveArticleUp(unsigned int position){
        if(position > 0){
            Article *buff = this->articles[position];
            this->articles[position] = this->articles[position - 1];
            this->articles[position - 1] = buff;
            this->setModified(true);
        }
    }

    void Document::moveArticleDown(unsigned int position){
        if(position < this->nbArticles - 1){
            Article *buff = this->articles[position];
            this->articles[position] = this->articles[position + 1];
            this->articles[position + 1] = buff;
            this->setModified(true);
        }
    }

    Document::~Document(){
		delete[] this->articles;
		this->articles = NULL;
    }
}
