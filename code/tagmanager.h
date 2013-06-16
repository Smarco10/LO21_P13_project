#ifndef TAGMANAGER_H
#define TAGMANAGER_H
#include"QHeader.h"

class Workspace;

#include"Note.h"

class Tag{

    QString noteId;
    QSet<QString> tags;
public:
    Tag(QString& nid,QSet<QString> t=QSet<QString>()):noteId(nid),tags(t){}
    QSet<QString>& getTagsList(){return tags;}
    QString& getNoteid(){return noteId;}
    void addTags(QSet<QString> tags);
    bool operator==(Tag& t);

};

class TagManager
{ //listTag
  QList<Tag> noteTags;
  QSet<QString> dictionary;
    static TagManager* instance;

    TagManager(){}
    ~TagManager(){}
    TagManager(const TagManager&);
    QList<Tag>::iterator&  findTag(Tag& t);

public:
    //Singleton

    //
    static TagManager* getInstance();
    void libererInstance();

    QList<Note*> noteListFromTagRestriction(QList<QString>);
    void updatedictionary(QList<QString> tags);
    QSet<QString>& getDictionary(QSet<QString>& s); // pour affichage
    void addNoteAndTags(Note& ,QSet<QString> s);
    void addTagsToNote(QString &nid,QSet<QString> s=QSet<QString>());
    QList<QString> &getTagslistForNote(QString& nid){
        Tag* temp=new Tag(nid);
        QList<QString> tgs=static_cast<Tag>(*findTag(*temp)).getTagsList().toList();
        return tgs;
    }



};




#endif // TAGMANAGER_H
