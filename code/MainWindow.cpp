#include "MainWindow.h"

MainWindow::MainWindow(QApplication* app):QMainWindow(){
    setWindowTitle(APP_TITLE);
    setWindowIcon(QIcon(APP_LOGO));

    zone = new QWidget;
    editor = new QWidget;
    editorNote = NULL;
    searchTags = new QWidget;

    zoneLay = new QHBoxLayout;
    tagsLay = new QVBoxLayout;
    editorLay = new QVBoxLayout;
    editor->setLayout(editorLay);

    //Partie tag manager
    searchTags->setLayout(tagsLay);

    inputTags = new QLineEdit;
    inputTags->setParent(searchTags);

    filterTags_n.setText("Filtres");
    filterTags_n.setParent(searchTags);
    filterTags_n.setAlignment(Qt::AlignHCenter);
    filterTags = new QListEditor(searchTags);

    //Créer une barre d'onglet Résultat et Corbeille
    tabs = new QTabWidget(searchTags);

    //créer un onglet Résultats
    outputNotes = new QListEditor(searchTags);
    tabs->addTab(outputNotes, "Résultat ( 0 )");

    //Créer un onglet Corbeille (lister les éléments suprimés en QAction (cliqued() => restaurer) + QAction "Vider la corbeille" + Qaction "tout restaurer"
    bin = new QWidget(searchTags);
    bin->setLayout(new QVBoxLayout);
    deleted = new QListEditor(bin);
    bin->layout()->addWidget(deleted);
    binDel = new QPushButton(ico_bin_empty, "", bin);
    binDel->setToolTip("Vider la Corbeille");
    bin->layout()->addWidget(binDel);
    tabs->addTab(bin, ico_bin_empty, "Corbeille ( 0 )");

    searchTags->layout()->addWidget(inputTags);
    searchTags->layout()->addWidget(&filterTags_n);
    searchTags->layout()->addWidget(filterTags);
    searchTags->layout()->addWidget(tabs);

    //Séparation des éléments
//Utiliser un gridLayout pour pouvoir redimensionner facilement les zones
    zone->setLayout(zoneLay);
    zone->layout()->addWidget(searchTags);
    zone->layout()->addWidget(editor);
    setCentralWidget(zone);

    //Menu
    tbarMisc = addToolBar("Miscellaneous");
    tbarOpen = addToolBar("OpenElements");

    //Menu Fichier
    file = menuBar()->addMenu("&Fichier");

    create = file->addMenu("&Nouveau");

    save = new QAction(ico_save, "Sauver", this);
    save->setDisabled(true);
    file->addAction(save);
    tbarMisc->addAction(save);

    print = new QAction(ico_print, "Imprimer", this);
    print->setDisabled(true);
    file->addAction(print);
    tbarMisc->addAction(print);

    //changer l'icon en full si la corbeille est non vide
    trash = new QAction(ico_bin_empty, "Supprimer", this);
    trash->setDisabled(true);
    file->addAction(trash);
    tbarMisc->addAction(trash);

    quit = new QAction(ico_quit, "Quitter", this);
    file->addAction(quit);
    tbarMisc->addAction(quit);

    article = new QAction(ico_article, "Article", this);
    create->addAction(article);
    tbarOpen->addAction(article);

    image = new QAction(ico_image, "Image", this);
    create->addAction(image);
    tbarOpen->addAction(image);

    audio = new QAction(ico_audio, "Enregistrement Audio", this);
    create->addAction(audio);
    tbarOpen->addAction(audio);

    video = new QAction(ico_video, "Enregistrement Video", this);
    create->addAction(video);
    tbarOpen->addAction(video);

    document = new QAction(ico_document, "Document", this);
    create->addAction(document);
    tbarOpen->addAction(document);

    //Menu Edition
    edit = menuBar()->addMenu("&Edition");

    //Menu Aide
    help = menuBar()->addMenu("&Aide");
    about = new QAction("À propos de " + APP_TITLE, this);
    help->addAction(about);

    //lien des menus
    QObject::connect(article, SIGNAL(triggered()), this, SLOT(articleCreator()));
    QObject::connect(image, SIGNAL(triggered()), this, SLOT(imageCreator()));
    QObject::connect(audio, SIGNAL(triggered()), this, SLOT(audioCreator()));
    QObject::connect(video, SIGNAL(triggered()), this, SLOT(videoCreator()));
    QObject::connect(document, SIGNAL(triggered()), this, SLOT(documentCreator()));

    QObject::connect(save, SIGNAL(triggered()), this, SLOT(saveNote()));
    QObject::connect(print, SIGNAL(triggered()), this, SLOT(printNote()));
    QObject::connect(trash, SIGNAL(triggered()), this, SLOT(deleteNote()));
    QObject::connect(quit, SIGNAL(triggered()), app, SLOT(quit()));

    QObject::connect(about, SIGNAL(triggered()), this, SLOT(aboutApp()));

    QObject::connect(outputNotes, SIGNAL(itemClicked(QListWidgetItem*)), outputNotes, SLOT(itActClicked(QListWidgetItem*)));
    QObject::connect(outputNotes, SIGNAL(itActClickedS(QListEditorItem*)), this, SLOT(openNote(QListEditorItem*)));

    QObject::connect(deleted, SIGNAL(itemDoubleClicked(QListWidgetItem*)), deleted, SLOT(itActDoubleClicked(QListWidgetItem*)));
    QObject::connect(deleted, SIGNAL(itActDoubleClickedS(QListEditorItem*)), this, SLOT(recoverNote(QListEditorItem*)));

    QObject::connect(binDel, SIGNAL(clicked()), this, SLOT(safeEmptyBin()));

    manager = NotesManager::getInstance(app);
    if(manager == NULL)
        return;

    //met à jour avec les notes préchargé dans le manager
    updateNotes();
}

MainWindow::~MainWindow(){
    //propose de vider la corbeille si elle n'est pas vide (condition déjà inclus dans la fct)
    safeEmptyBin();

    NotesManager::libererInstance();
}

void MainWindow::warning(){
    QMessageBox::warning(NULL, "Attention", "Ce menu n'est pas encore implémenté", QMessageBox::Ok);
}

void MainWindow::articleCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Article *art = dynamic_cast<Article*>(&manager->getNewNote("Article", ""));
    noteCreator(art);
}

void MainWindow::imageCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Image* img = dynamic_cast<Image*>(&manager->getNewNote("Image", ""));
    noteCreator(img);
}

void MainWindow::audioCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Audio *aud = dynamic_cast<Audio*>(&manager->getNewNote("Audio", ""));
    noteCreator(aud);
}

void MainWindow::videoCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Video* vid = dynamic_cast<Video*>(&manager->getNewNote("Video", ""));
    noteCreator(vid);
}

void MainWindow::documentCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Document* doc = dynamic_cast<Document*>(&manager->getNewNote("Document", ""));
    noteCreator(doc);
}

void MainWindow::noteCreator(Note* n){
    //Vérifie si l'object existe dans le manager sinon le créé
    QListEditorItem* act = newItem(n);
    outputNotes->addItem(act);
    tabs->setTabText(tabs->indexOf(outputNotes), "Résultat" + QString(((outputNotes->count() > 1) ? "s ( " : " ( ")) + QString::number(outputNotes->count()) + " )");
    openNote(act);
}

QListEditorItem* MainWindow::newItem(Note* n){
    if(n == NULL)
        return NULL;
    return new QListEditorItem(manager->getNoteIcon(n), n->getTitle(), manager->noteEdConstructor(n, editor));
}

void MainWindow::updateNotes(){
    //Récupère toutes les notes du manager et les ajoutes à l'interface
    for(unsigned int i = 0; i < manager->getNbNotes(); i++)
        noteCreator(manager->getNote(i));
}

void MainWindow::openNote(QListEditorItem *o){
    if(editorNote != NULL){
        editor->layout()->removeWidget(editorNote->getRessource());
        editorNote->getRessource()->hide();
    }

    editorNote = o;
    editor->layout()->addWidget(editorNote->getRessource());
    editorNote->getRessource()->show();

    outputNotes->setCurrentItem(o);

    //MàJ des icons
    save->setEnabled(true);
    print->setEnabled(true);
    trash->setEnabled(true);
}

void MainWindow::printNote(){
    //demander de sauver la note en cours d'édition
    //exporter dans le format voulu (fct de l'onglet sinon imprime le fichier tel quel)
    //imprimer le fichier
    warning();
}

void MainWindow::saveNote(){
    //demande de sauver la note en cours d'édition
    manager->saveNote(editorNote->getRessource()->getRessource());
    save->setEnabled(false);
}

void MainWindow::deleteNote(){
    //enlève l'interface
    editor->layout()->removeWidget(editorNote->getRessource());
    editorNote->getRessource()->hide();

    //retire la note de la liste des notes
    QListEditorItem *item = outputNotes->takeItem(outputNotes->currentRow());
    //QMessageBox::information(NULL, "info", "info: " + QString::number((int)(item == NULL)), QMessageBox::Ok);

    //ajoute la note à la liste des supprimées
    deleted->addItem(item);

    editorNote = NULL;

    //MàJ des icons
    save->setEnabled(false);
    print->setEnabled(false);
    trash->setEnabled(false);

    //MàJ des onglets
    tabs->setTabText(tabs->indexOf(outputNotes), "Résultat" + QString(((outputNotes->count() > 1) ? "s ( " : " ( ")) + QString::number(outputNotes->count()) + " )");

    tabs->setTabIcon(tabs->indexOf(bin), ico_bin_full);
    tabs->setTabText(tabs->indexOf(bin), "Corbeille ( " + QString::number(deleted->count()) + " )");
}

void MainWindow::recoverNote(QListEditorItem *item){
    //restaurer la note dans la liste outputNotes
    deleted->takeItem(deleted->currentRow());
    outputNotes->addItem(item);

    //MàJ des onglets
    tabs->setTabText(tabs->indexOf(outputNotes), "Résultat" + QString(((outputNotes->count() > 1) ? "s ( " : " ( ")) + QString::number(outputNotes->count()) + " )");

    if(deleted->count() > 0)
        tabs->setTabIcon(tabs->indexOf(bin), ico_bin_full);
    else
        tabs->setTabIcon(tabs->indexOf(bin), ico_bin_empty);

    tabs->setTabText(tabs->indexOf(bin), "Corbeille ( " + QString::number(deleted->count()) + " )");
}

void MainWindow::safeEmptyBin(){
    //demander si on est sur de supprimer toutes noutes définitivement?
    if(deleted->count() == 0)
        return;

    //création de la fenêtre
    QDialog *altWindow = new QDialog(this);
    altWindow->setWindowTitle("Vider la corbeille");
    altWindow->setWindowIcon(ico_bin_empty);
    QHBoxLayout *altWindowLay = new QHBoxLayout;
    altWindow->setLayout(altWindowLay);

    //partie icon
    QLabel *logo = new QLabel(altWindow);
    logo->setPixmap(ico_bin_full.pixmap(ico_bin_full.availableSizes().at(0)));
    altWindow->layout()->addWidget(logo);

    //partie texte
    QWidget *text = new QWidget(altWindow);
    text->setLayout(new QVBoxLayout());
    altWindow->layout()->addWidget(text);

    QLabel *quest = new QLabel("Etes-vous sur de vouloir vider la corbeille?", altWindow);
    text->layout()->addWidget(quest);

    QLabel *info = new QLabel("Cette action est <b>irreversible</b>.", altWindow);
    text->layout()->addWidget(info);

    //partie boutons
    QWidget *controls = new QWidget(altWindow);
    controls->setLayout(new QHBoxLayout());

    QPushButton *yes = new QPushButton(controls->style()->standardIcon(QStyle::SP_DialogApplyButton), "");
    yes->setToolTip("Vide la corbeille et supprime les fichier physiques");
    controls->layout()->addWidget(yes);

    QObject::connect(yes, SIGNAL(clicked()), this, SLOT(emptyBin()));
    QObject::connect(yes, SIGNAL(clicked()), altWindow, SLOT(close()));

    QPushButton *cancel = new QPushButton(controls->style()->standardIcon(QStyle::SP_DialogCancelButton), "");
    cancel->setToolTip("Annule et retourne au programme");
    controls->layout()->addWidget(cancel);

    QObject::connect(cancel, SIGNAL(clicked()), altWindow, SLOT(close()));

    text->layout()->addWidget(controls);

    altWindow->exec();
}

void MainWindow::emptyBin(){
    //supprime les notes et leur fichier associé ainsi que leur NoteEditor
    for(int i = 0; i < deleted->count(); i++){
        manager->deleteNote(deleted->item(i)->getRessource()->getRessource());
        delete deleted->item(i)->getRessource();
    }
    deleted->clear();

    tabs->setTabIcon(tabs->indexOf(bin), ico_bin_empty);
    tabs->setTabText(tabs->indexOf(bin), "Corbeille ( 0 )");
}

void MainWindow::aboutApp(){
    //création de la fenêtre
    QDialog *altWindow = new QDialog(this);
    altWindow->setWindowTitle("À propos de " + APP_TITLE);
    QHBoxLayout *altWindowLay = new QHBoxLayout;
    altWindow->setLayout(altWindowLay);

    //partie logo
    QPushButton *bt = new QPushButton(altWindow);
    QLabel *logo = new QLabel(bt);
    logo->setPixmap(QPixmap(APP_LOGO));
    bt->setFixedSize(logo->pixmap()->size() + QSize(10,10));
    logo->move(5, 5);
    altWindow->layout()->addWidget(bt);
    QObject::connect(bt, SIGNAL(clicked()), altWindow, SLOT(close()));

    //partie texte
    QWidget *text = new QWidget(altWindow);
    text->setLayout(new QVBoxLayout());
    altWindow->layout()->addWidget(text);

    QLabel *title = new QLabel(APP_TITLE, altWindow);
    title->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    title->setFont(QFont(title->font().family(), 24));
    text->layout()->addWidget(title);

    QLabel *desc = new QLabel("Application développée dans le cadre d'un projet de LO21 à l'UTC au printemps 2013.", altWindow);
    text->layout()->addWidget(desc);

    QLabel *dev = new QLabel("<u>Développeurs</u>:<BLOCKQUOTE>Jonathan DIGUET<br/><br/>Marc-Antoine MARTIN</BLOCKQUOTE>", altWindow);
    text->layout()->addWidget(dev);

    //partie texte 2
    QWidget *text2 = new QWidget(text);
    text2->setLayout(new QHBoxLayout());
    text->layout()->addWidget(text2);

    QLabel *link = new QLabel("<a href=\"https://github.com/Smarco10/LO21_P13_project\">https://github.com/Smarco10/LO21_P13_project</a> ", altWindow);
    link->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    text2->layout()->addWidget(link);

    QLabel *credits = new QLabel("© <i>UTC - 2013</i> ", altWindow);
    credits->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    text2->layout()->addWidget(credits);

    altWindow->exec();
}
