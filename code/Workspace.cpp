#include "Workspace.h"

Workspace::Workspace(const QString& p):QWidget(), pathWS(p),modified(false){
    //Modification du dossier de travail:

    dom = new QDomDocument("workspace");
    QFile xml_doc(getPath() + WORKSPACE_FILENAME);

    if(xml_doc.exists()){
        if(!xml_doc.open(QIODevice::ReadOnly)){
            xml_doc.close();
            QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
            return;
        }

        if (!dom->setContent(&xml_doc)){
            xml_doc.close();
            QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
            return;
        }

        xml_doc.close();

        check();
    } else
        dom->setContent(QString("<?xml version='1.0' encoding='UTF-8'?>\n<notes/>"));
}

QList<QString> Workspace::listNotes(){
    QList<QString> notes;
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("note");

    for(int i = 0; i < nd.count(); i++)
        notes.push_back(nd.at(i).toElement().attribute("path"));

    return notes;
}

QList<QString> Workspace::listNotesD(){
    QList<QString> notes;
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("noteDeleted");

    for(int i = 0; i < nd.count(); i++)
        notes.push_back(nd.at(i).toElement().attribute("path"));

    return notes;
}

QList<QString> Workspace::listTags(){
    QList<QString> tags;
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("note");

    for(int i = 0; i < nd.count(); i++)
        tags.push_back(nd.at(i).toElement().attribute("tags"));

    nd = dom_el.elementsByTagName("noteDeleted");

    for(int i = 0; i < nd.count(); i++)
        tags.push_back(nd.at(i).toElement().attribute("tags"));

    return tags;
}

QString Workspace::getType(const QString& path){
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("note");

    for(int i = 0; i < nd.count(); i++)
        if(nd.at(i).toElement().attribute("path") == path)
            return nd.at(i).toElement().attribute("type");

    nd = dom_el.elementsByTagName("noteDeleted");

    for(int i = 0; i < nd.count(); i++)
        if(nd.at(i).toElement().attribute("path") == path)
            return nd.at(i).toElement().attribute("type");

    return "";
}

bool Workspace::isNote(const QString& path){
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("note");

    for(int i = 0; i < nd.count(); i++)
        if(nd.at(i).toElement().attribute("path") == path)
            return true;

    nd = dom_el.elementsByTagName("noteDeleted");

    for(int i = 0; i < nd.count(); i++)
        if(nd.at(i).toElement().attribute("path") == path)
            return true;

    return false;
}

void Workspace::addNote(const QString& path, const QString& type, const QList<QString>& tags){
    QDomElement dom_el = dom->documentElement();

    // Vérifie si la note n'existe pas déjà sinon on la met à jour
    if(isNote(path)){
        updateNote(path, type, tags);
        return;
    }

    //convertis la liste en chaine
    QString tagsS = "";
    for(int i = 0; i < tags.size(); i++)
        tagsS += tags.at(i) + ";";

    //création de la note
    QDomElement newNote = dom->createElement("note");
    newNote.setAttribute("path", path);
    newNote.setAttribute("type", type);
    newNote.setAttribute("tags", tagsS);

    //ajout de la note
    dom_el.appendChild(newNote);

    modified = true;
}

void Workspace::noteToD(const QString& path){
    QDomElement dom_el = dom->documentElement();

    // Vérifie si la note existe
    if(!isNote(path))
        return;

    QDomNodeList nd = dom_el.elementsByTagName("note");

    for(int i = 0; i < nd.count(); i++)
        if(nd.at(i).toElement().attribute("path") == path)
            nd.at(i).toElement().setTagName("noteDeleted");

    modified = true;
}

void Workspace::deletedToN(const QString& path){
    QDomElement dom_el = dom->documentElement();

    // Vérifie si la note existe
    if(!isNote(path))
        return;

    QDomNodeList nd = dom_el.elementsByTagName("noteDeleted");

    for(int i = 0; i < nd.count(); i++)
        if(nd.at(i).toElement().attribute("path") == path)
            nd.at(i).toElement().setTagName("note");

    modified = true;
}

void Workspace::updateNote(const QString& path, const QString& type, const QList<QString>& tags){
    QDomElement dom_el = dom->documentElement();
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.attribute("path") == path){
            QDomElement newEl = el;
            newEl.setAttribute("type", type);
            //convertis la liste en chaine
            QString tagsS = "";
            for(int i = 0; i < tags.size(); i++)
                tagsS += tags.at(i) + ";";
            newEl.setAttribute("tags", tagsS);
            dom_el.replaceChild(newEl, el);
            break;
        }
        nd = nd.nextSibling();
    }

    modified = true;
}

void Workspace::deleteNote(const QString& path){
    QDomElement dom_el = dom->documentElement();
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.attribute("path") == path){
            dom_el.removeChild(el);
            //supprime le fichier correspondant
            QFile fichier(getPath() + path);
            fichier.remove();
            break;
        }
        nd = nd.nextSibling();
    }

    modified = true;
}

void Workspace::check(){
    //vérifie que toutes les notes sont présentent dans le dossier
    //si absence enlève l'entrée de la note du workspace

    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("note");

    for(int i = 0; i < nd.count(); i++){
        QFile note(getPath() + nd.at(i).toElement().attribute("path"));
        if(!note.exists()){
            dom_el.removeChild(nd.at(i).toElement());
            modified = true;
        }
    }

    //check les notes supprimées:
    nd = dom_el.elementsByTagName("noteDeleted");

    for(int i = 0; i < nd.count(); i++){
        QFile note(getPath() + nd.at(i).toElement().attribute("path"));
        if(!note.exists()){
            dom_el.removeChild(nd.at(i).toElement());
            modified = true;
        }
    }
}

void Workspace::updateWorkspace(){
    QString update = dom->toString();
    QFile fichier(getPath() + WORKSPACE_FILENAME);
    if(!fichier.open(QIODevice::WriteOnly)){
        fichier.close();
        return;
    }
    QTextStream stream(&fichier);
    stream << update;
    fichier.close();

    modified = false;
}
