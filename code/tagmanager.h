﻿#ifndef TAGMANAGER_H
#define TAGMANAGER_H
#include"QHeader.h"
class TagManager
{ //listTag
  QSet<Tag> noteTags;

  TagManager* instance;
    TagManager();
    TagManager(const TagManager&);

public:
    //Singleton

    //
    static TagManager* getInstance();
    static void libererInstance();

    QList<Note*>& noteListFromTagRestriction(QList<QString>);
    void updatedictionary(QList<Tag> tag);
    QSet<QString>& getdictionary(QSet<QString>& s); // pour affichage
    void addNoteAndTags(Note& ,QSet<QString> s);
    void addTagsToNote(QString nid,QSet<QString> s);


    //
    //


};

#endif // TAGMANAGER_H

class Tag{

    QString noteId;
    QSet<QString> tags;
public:
    Tag(QString nid,QSet<QString> t):noteId(nid()),tags(t){}
    QSet<QString>& getTagsList(){return tags;}
    QString& getNoteid(){return noteId;}
    void addTags(QList<QString> tags);
};