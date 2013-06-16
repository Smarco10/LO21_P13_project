#include "tagmanager.h"


TagManager* TagManager::instance = NULL;
TagManager* TagManager::getInstance(){
    if(!instance) instance=new TagManager;

    return instance;
}

void TagManager::libererInstance(){
    if (instance) delete instance;
    instance=0;
 }
void TagManager::addNoteAndTags(Note &n, QSet<QString> s){
    Tag* t=new Tag(n.getId(),s);
    if(this->findTag(*t) !=noteTags.end()){
        noteTags.insert(noteTags.end(),*t);
    }


}

void TagManager::addTagsToNote(QString& nid, QSet<QString> s){
    Tag* t=new Tag(nid);
    QList<Tag>::iterator it=this->findTag(*t);
    if(it!=noteTags.end()){
        (static_cast<Tag>(*it)).addTags(s);
    }

}
QList<Note*> TagManager::noteListFromTagRestriction(QList<QString>lst){
    QList<Note*> noteList;
    QList<QString> idlst;
    QList<Tag> tglst;
    QList<Tag> tglst2;
    tglst.append(noteTags);

    for(QList<QString>::iterator it=lst.begin();it!=lst.end();++it){
        // pour chaque element dans la liste de tag
        for(QList<Tag>::iterator itT=tglst.begin();itT!=tglst.end();++itT){
            // pour chaque tag recherche dans la liste de tag
            if(std::find(static_cast<Tag>(*itT).getTagsList().begin(),static_cast<Tag>(*itT).getTagsList().end(),static_cast<QString>(*it)) !=static_cast<Tag>(*itT).getTagsList().end())
             {
                tglst2.push_back(static_cast<Tag>(*itT));
            }

        }
        tglst=tglst2;
        tglst2.clear();
    }
    for(QList<Tag>::iterator itT=tglst.begin();itT!=tglst.end();++itT){
    idlst.push_back(static_cast<Tag>(*itT).getNoteid());
    }
    NotesManager* nm=NotesManager::getInstance();
  for(QList<QString>::iterator itS=idlst.begin();itS!=idlst.end();++itS){
      noteList.push_back(&nm->getNote(static_cast<QString>(*itS)));
  }

}

void TagManager::updatedictionary(QList<QString> tags){
 for(QList<QString>::iterator it=tags.begin();it!=tags.end();++it){
     dictionary.insert((*it));
}

}

QSet<QString>& TagManager::getdictionary(QSet<QString>& s){return dictionary;}

bool Tag::operator ==(Tag& t){
    return this->getNoteid()==t.getNoteid();
}
QList<Tag>::iterator&  TagManager::findTag(Tag& t){
        QList<Tag>::iterator it=noteTags.begin();
        while(it!=noteTags.end()){
            if((Tag)(*it)==t )
                return it;
            ++it;
      }
    return it;
}
void Tag::addTags(QSet<QString> tags){
    this->tags.operator +=(tags);

}
