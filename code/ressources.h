#ifndef RESSOURCES_H
#define RESSOURCES_H

#include "QHeader.h"

static QString APP_TITLE("BanaNotes");
static QString APP_LOGO("logo.png");
static QString WORKSPACE_FILENAME(".workspace");
static QString CONFIG_FILENAME(".BanaNoteConfig");

//icons
#define ico_save QIcon("icons/save.png")
#define ico_print QIcon("icons/print.png")
#define ico_quit QIcon("icons/quit.png")
#define ico_article QIcon("icons/article.png")
#define ico_image QIcon("icons/image.png")
#define ico_audio QIcon("icons/audio.png")
#define ico_video QIcon("icons/video.png")
#define ico_document QIcon("icons/document.png")
#define ico_change QIcon("icons/change.png")
#define ico_bin_empty QIcon("icons/bin_empty.png")
#define ico_bin_full QIcon("icons/bin_full.png")
//rajouter un '?' au milieu de l'icon
#define ico_unknown QIcon("icons/unknown.png")

#endif // RESSOURCES_H
