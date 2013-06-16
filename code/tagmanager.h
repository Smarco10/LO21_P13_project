#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include"Note.h"
#include "NotesManager.h"
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
    QSet<QString>& getdictionary(QSet<QString>& s); // pour affichage
    void addNoteAndTags(Note& ,QSet<QString> s);
    void addTagsToNote(QString &nid,QSet<QString> s=QSet<QString>());


    //
    //


};




#endif // TAGMANAGER_H
