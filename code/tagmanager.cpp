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
