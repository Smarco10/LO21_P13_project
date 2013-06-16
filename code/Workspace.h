#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "QHeader.h"
#include"tagmanager.h"
///\class Workspace
///Gère la création physique des notes, les dossiers de travail
///gère la sauvegarde des notes leurs suppression/restauration

/* Exemple de fichier ".workspace"
<?xml version='1.0' encoding='UTF-8'?>
<notes>
 <note path="1370104481823" tags="art;note" type="Article"/>
 <note path="1370116693235" tags="note;film;chaplin;yellow" type="Video"/>
</notes>
*/

class Workspace: public QWidget{
    QDomDocument *dom;
    bool modified;
    void updateWorkspace();
    QString pathWS;

public:
    Workspace(const QString& p = ".");
    ~Workspace(){if(modified) updateWorkspace();}

    QString getPath() {return pathWS;}
    void setPath(const QString& p = ".");

    //read
    QList<QString> listNotes();
    QList<QString> listNotesD();
    QList<QString> listTags();
    void noteToD(const QString& path);
    void deletedToN(const QString& path);
   QString getType(const QString& path);
    QString getTags(const QString& path){/*TagManager::getInstance()->getDictionary();*/}
    bool isNote(const QString& path);

    //write
    void addNote(const QString& path, const QString& type, const QList<QString>& tags);
    void updateNote(const QString& path, const QString& type, const QList<QString>& tags);
    void deleteNote(const QString& path);

    void check();
};

#endif // WORKSPACE_H
