#ifndef WORKSPACE_H
#define WORKSPACE_H

#include "QHeader.h"

/* Exemple de fichier ".workspace"
<?xml version='1.0' encoding='ISO-8859-1'?>
<notes>
 <note path="1370104481823" tags="art;note" type="Article"/>
 <note path="1370116693235" tags="film;chaplin;yellow" type="Video"/>
</notes>
*/

class Workspace: public QWidget{
    QDomDocument *dom;
    QString path;
    bool modified;
    void updateWorkspace();
public:
    Workspace();
    ~Workspace(){if(modified) updateWorkspace();}

    QString getPath() {return path;}
    void setPath(const QString& p) {path = p;
                                    //Vérifie que path n'est pas vide sinon met le dossier courant par défaut
                                    if(path.isEmpty()) path == ".";
                                    //on supprime le dernier '/' si présent car ajouté automatiquement
                                    if(path.at(path.size() - 1) == QChar('/')) path.remove(path.size() - 1, 1);}

    //read
    QString listNotes();
    QString listTags();
    QString getType(const QString& path);
    QString getTags(const QString& path);
    bool isNote(const QString& path);

    //write
    void addNote(const QString& path, const QString& type, const QString& tags);
    void updateNote(const QString& path, const QString& type, const QString& tags);
    void deleteNote(const QString& path);

    void check();
};

#endif // WORKSPACE_H
