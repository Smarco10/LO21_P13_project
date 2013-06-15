#include "Config.h"

Config::Config():modified(false){
    dom = new QDomDocument("config");
    QFile xml_doc(CONFIG_FILENAME);

    if(xml_doc.exists()){
        if(!xml_doc.open(QIODevice::ReadOnly)){
            xml_doc.close();
            QMessageBox::warning(NULL,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
            return;
        }

        if (!dom->setContent(&xml_doc)){
            xml_doc.close();
            QMessageBox::warning(NULL,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
            return;
        }

        xml_doc.close();

        check();
    } else
        dom->setContent(QString("<?xml version='1.0' encoding='UTF-8'?>\n<config>\n<lastWorkspace path=\".\" />\n</config>"));
}

void Config::check(){
    //parcours tout les worspace 1 par 1 et supprime les inexistants
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("workspace");

    for(int i = 0; i < nd.count(); i++){
        QDir ws(nd.at(i).toElement().attribute("path"));
        //vérifie que le fichier workspace existe dans le fichier
        if(!ws.exists(WORKSPACE_FILENAME)){
            //suprime du xml
            dom_el.removeChild(nd.at(i).toElement());
            modified = true;
        }
    }
}

bool Config::isWS(const QString& workspacePath){
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("workspace");

    for(int i = 0; i < nd.count(); i++)
        if(nd.at(i).toElement().attribute("path") == workspacePath)
            return true;

    return false;
}

unsigned int Config::nbWS(){
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("workspace");
    return nd.size();
}

QString Config::lastWS(){
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("lastWorkspace");

    return nd.at(0).toElement().attribute("path");
}

void Config::updateLastWS(const QString& path){
    //Mise à jour du lastWS
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("lastWorkspace");
    nd.at(0).toElement().setAttribute("path", path);
}

bool Config::newWS(const QString& wsPath){
    QDomElement dom_el = dom->documentElement();
    QString workspacePath = wsPath;
    //On corrige la fin du Worksace pour que ça devienne un chemin de dossier
    if(workspacePath.at(workspacePath.size() - 1) != QChar('\\')) workspacePath.push_back(QChar('\\'));

    //Vérifier que le WS n'existe pas déjà
    if(isWS(workspacePath))
        return false;

    //regarde si le dossier existe si non le créer si échec sort
    QDir ws(workspacePath);
    if(!ws.exists())
        if(!ws.mkdir(workspacePath))
            return false;

    updateLastWS(workspacePath);

    //création du WS
    QDomElement newWorkspace = dom->createElement("workspace");
    newWorkspace.setAttribute("path", workspacePath);

    //ajout du WS
    dom_el.appendChild(newWorkspace);

    modified = true;

    return true;
}

bool Config::cloneWS(const QString& wsPathSrc, const QString& wsPathDest){
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("workspace");

    //créer la nouvelle entrée quitte si échec
    if(!newWS(wsPathDest))
        return false;

    for(int i = 0; i < nd.count(); i++){
        if(nd.at(i).toElement().attribute("path") == wsPathSrc){
            Workspace ws(wsPathSrc);

            QList<QString> notes = ws.listNotes();
            for(int j = 0; j < notes.size(); j++)
                //copie la note de Src vers Dest
//renommer la note avec un nouvel ID (ne pas oublier dans le .workspace)
                QFile::copy(wsPathSrc + notes.at(j), wsPathDest + ((wsPathDest.at(wsPathDest.size() - 1) != QChar('\\')) ? "\\" : "") + notes.at(j));

            //copie le fichier WS correspondant
            QFile::copy(wsPathSrc + WORKSPACE_FILENAME, wsPathDest + ((wsPathDest.at(wsPathDest.size() - 1) != QChar('\\')) ? "\\" : "") + WORKSPACE_FILENAME);

            break;
        }
    }
}

void Config::deleteWS(const QString& workspacePath){
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("workspace");

    //Vérifie que le dernier workspace ouvert est celui qui vas être supprimé
    if(lastWS() == workspacePath)
        if(nbWS() > 1)
            //on affecte le premier élément
            updateLastWS(nd.at(0).toElement().attribute("path"));
        else
            //on affecte à NULL
            updateLastWS("");

    for(int i = 0; i < nd.count(); i++){
        if(nd.at(i).toElement().attribute("path") == workspacePath){
            //supprime tout les éléments du workspace
            Workspace ws(workspacePath);

            QList<QString> notes = ws.listNotes();
            for(int j = 0; j < notes.size(); j++)
                ws.deleteNote(notes.at(j));

            //suprime du xml
            dom_el.removeChild(nd.at(i).toElement());

            //supprime le fichier correspondant
            QDir wsDir(workspacePath);
            wsDir.remove(WORKSPACE_FILENAME);
            if(wsDir.count() == 0)
                wsDir.rmdir(workspacePath);

            modified = true;
            break;
        }
    }
}

void Config::updateConfig(){
    QString update = dom->toString();
    QFile fichier(CONFIG_FILENAME);
    if(!fichier.open(QIODevice::WriteOnly)){
        fichier.close();
        return;
    }
    QTextStream stream(&fichier);
    stream << update;
    fichier.close();

    modified = false;
}

QList<QString> Config::listWS(){
    QList<QString> lst;
    QDomElement dom_el = dom->documentElement();
    QDomNodeList nd = dom_el.elementsByTagName("workspace");

    for(int i = 0; i < nd.count(); i++)
        lst.push_back(nd.at(i).toElement().attribute("path"));

    return lst;
}

ConfigManager::ConfigManager(QWidget *parent):QDialog(parent){
    setParent(parent);
    setWindowTitle("Espaces de travail");

    conf = new Config;

    altWindowLay = new QVBoxLayout;
    setLayout(altWindowLay);

    //partie texte
    info = new QLabel("Veuillez choisir un espace de travail:", this);
    layout()->addWidget(info);

    //partie listes
    listes = new QWidget(this);
    listesLay = new QHBoxLayout;
    listes->setLayout(listesLay);
    layout()->addWidget(listes);

    workspaces = new QListWidget(listes);
    listes->layout()->addWidget(workspaces);

    notes = new QLabel("Cliquez sur un workspace pour afficher ses notes");
    listes->layout()->addWidget(notes);

    //partie boutons
    buttons = new QWidget(this);
    buttonsLay = new QHBoxLayout;
    buttons->setLayout(buttonsLay);

    open = new QPushButton("Ouvrir");
    open->setToolTip("Ouvrir le workspace sélectionné");
    buttons->layout()->addWidget(open);

    clone = new QPushButton("Cloner");
    clone->setToolTip("Cloner le workspace sélectionné");
    buttons->layout()->addWidget(clone);

    del = new QPushButton("Supprimer");
    del->setToolTip("Suprimer le workspace sélectionné");
    buttons->layout()->addWidget(del);

    create = new QPushButton("Nouveau");
    create->setToolTip("Créer un nouveau workspace");
    buttons->layout()->addWidget(create);

    layout()->addWidget(buttons);

    updateGUI();

    QObject::connect(workspaces, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showNotes(QListWidgetItem*)));
    QObject::connect(workspaces, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(showNotes(QListWidgetItem*)));
    QObject::connect(open, SIGNAL(clicked()), this, SLOT(loadWS()));
    QObject::connect(clone, SIGNAL(clicked()), this, SLOT(cloneWS()));
    QObject::connect(del, SIGNAL(clicked()), this, SLOT(safeDel()));
    QObject::connect(create, SIGNAL(clicked()), this, SLOT(newWS()));

    exec();
}

void ConfigManager::safeDel(){
    //création de la fenêtre
    QDialog *altWindow = new QDialog(this);
    altWindow->setWindowTitle("Supprimer l'espace de travail");
    QVBoxLayout *altWindowLay = new QVBoxLayout;
    altWindow->setLayout(altWindowLay);

    //partie texte
    QLabel *quest = new QLabel("Etes-vous sur de vouloir supprimer l'espace de traveil?", altWindow);
    altWindow->layout()->addWidget(quest);

    QLabel *info = new QLabel("Cette action est <b>irreversible</b>.", altWindow);
    altWindow->layout()->addWidget(info);

    //partie boutons
    QWidget *controls = new QWidget(altWindow);
    controls->setLayout(new QHBoxLayout());

    QPushButton *yes = new QPushButton(controls->style()->standardIcon(QStyle::SP_DialogApplyButton), "");
    yes->setToolTip("Vide la corbeille et supprime les fichier physiques");
    controls->layout()->addWidget(yes);

    QObject::connect(yes, SIGNAL(clicked()), this, SLOT(delWS()));
    QObject::connect(yes, SIGNAL(clicked()), altWindow, SLOT(close()));

    QPushButton *cancel = new QPushButton(controls->style()->standardIcon(QStyle::SP_DialogCancelButton), "");
    cancel->setToolTip("Annule et retourne au programme");
    controls->layout()->addWidget(cancel);

    QObject::connect(cancel, SIGNAL(clicked()), altWindow, SLOT(close()));

    altWindow->layout()->addWidget(controls);

    altWindow->exec();
}

void ConfigManager::delWS(){
    conf->deleteWS(workspaces->currentItem()->text());
    QListWidgetItem *item = workspaces->takeItem(workspaces->currentRow());
    delete item;
    updateGUI();
}

void ConfigManager::newWS(){
    QString path = QFileDialog::getExistingDirectory(this);
    //si on a pas sélectionné sur annuler
    if(path.isEmpty())
        return;

    if(conf->newWS(path))
        updateGUI();
}

void ConfigManager::cloneWS(){
    QString dossier = QFileDialog::getExistingDirectory(this);
    //si on a pas sélectionné sur annuler
    if(dossier.isEmpty())
        return;

    if(conf->cloneWS(workspaces->currentItem()->text(), dossier))
        updateGUI();
}

void ConfigManager::loadWS(){
    //modifie l'espace de travail
    pathWS = workspaces->currentItem()->text();
    conf->updateLastWS(pathWS);
    this->close();
}

void ConfigManager::showNotes(QListWidgetItem* item){
    QString nts = "notes:\n";

    Workspace ws(item->text());
    QList<QString> listeNotes = ws.listNotes();

    for(int i = 0; i < listeNotes.size(); i++)
        nts += listeNotes.at(i) + " : " + ws.getType(listeNotes.at(i)) + "\n";

    nts += "\ncorbeille:\n";

    listeNotes = ws.listNotesD();

    for(int i = 0; i < listeNotes.size(); i++)
        nts += listeNotes.at(i) + " : " + ws.getType(listeNotes.at(i)) + "\n";

    notes->setText(nts);
}

void ConfigManager::updateGUI(){
    if(conf->nbWS() > 0){
        open->setEnabled(true);
        clone->setEnabled(true);
        del->setEnabled(true);
    } else {
        open->setEnabled(false);
        clone->setEnabled(false);
        del->setEnabled(false);
        notes->setText("");
    }

    workspaces->clear();

    //ajout des workspaces à la liste
    QList<QString> listeWS = conf->listWS();
    for(int i = 0; i < listeWS.size(); i++){
        workspaces->addItem(new QListWidgetItem(listeWS.at(i), workspaces));
        if(listeWS.at(i) == conf->lastWS()){
            workspaces->setCurrentItem(workspaces->item(i));
            showNotes(workspaces->item(i));
        }
    }
}
