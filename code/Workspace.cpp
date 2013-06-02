#include "Workspace.h"

Workspace::Workspace(const QString& p):QWidget(),path(p){
    //Modification du dossier de travail:

    //on supprime le dernier '/' si présent car ajouté automatiquement
    if(path.at(path.size() - 1) == QChar('/')) path.remove(path.size() - 1, 1);

    //on modifie le dossier courant
    QDir::setCurrent(path);

    dom = new QDomDocument("workspace");
    QFile xml_doc(WORKSPACE_FILENAME);

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

        modified = false;
        xml_doc.close();
    } else
        dom->setContent(QString("<?xml version='1.0' encoding='UTF-8'?>\n<notes>\n</notes>"));
}

QString Workspace::listNotes(){
    QString notes = "";
    QDomElement dom_el = dom->documentElement();
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.hasAttribute("path"))
            notes += el.attribute("path") + "\n";
        nd = nd.nextSibling();
    }

    return notes;
}

QString Workspace::listTags(){
    QString tags = "";
    QDomElement dom_el = dom->documentElement();
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.hasAttribute("tags"))
            tags += el.attribute("tags") + ";";
        nd = nd.nextSibling();
    }

    return tags;
}

QString Workspace::getType(const QString& path){
    QDomElement dom_el = dom->documentElement();
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.attribute("path") == path && el.hasAttribute("type"))
            return el.attribute("type");
        nd = nd.nextSibling();
    }

    return "";
}

bool Workspace::isNote(const QString& path){
    QDomElement dom_el = dom->documentElement();
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.attribute("path") == path)
            return true;
        nd = nd.nextSibling();
    }

    return false;
}

void Workspace::addNote(const QString& path, const QString& type, const QString& tags){
    QDomElement dom_el = dom->documentElement();

    if(isNote(path))
        return;

    //création de la note
    QDomElement newNote = dom->createElement("note");
    newNote.setAttribute("path", path);
    newNote.setAttribute("type", type);
    newNote.setAttribute("tags", tags);

    //ajout de la note
    dom_el.appendChild(newNote);

    modified = true;
}

void Workspace::updateNote(const QString& path, const QString& type, const QString& tags){
    QDomElement dom_el = dom->documentElement();
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.attribute("path") == path){
            QDomElement newEl = el;
            newEl.setAttribute("type", type);
            newEl.setAttribute("tags", tags);
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
    QDomNode nd = dom_el.firstChild();

    while(!nd.isNull()){
        QDomElement el = nd.toElement();
        if(el.tagName() == "note" && el.hasAttribute("path")){
            QFile note(el.attribute("path"));
            if(!note.exists())
                dom_el.removeChild(el);
        }
        nd = nd.nextSibling();
    }

    modified = true;
}

void Workspace::updateWorkspace(){
    QString update = dom->toString();
    QFile fichier(WORKSPACE_FILENAME);
    if(!fichier.open(QIODevice::WriteOnly)){
        fichier.close();
        return;
    }
    QTextStream stream(&fichier);
    stream << update;
    fichier.close();

    modified = false;
}
