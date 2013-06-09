#include "MainWindow.h"

MainWindow::MainWindow(QApplication* app){
    manager = &NotesManager::getInstance();

    setWindowTitle(APP_TITLE);
    setWindowIcon(QIcon(APP_LOGO));

    zone = new QWidget;
    editorNote = NULL;
    searchTags = new QWidget;

    tagsLay = new QVBoxLayout;
    zoneLay = new QHBoxLayout;

    mapper = new QSignalMapper;

    //Partie tag manager
    searchTags->setLayout(tagsLay);

    inputTags = new QLineEdit;
    inputTags->setParent(searchTags);
    inputTags->setText("All");

    filterTags_n.setText("Filtres:");
    filterTags_n.setParent(searchTags);
    filterTags_n.setAlignment(Qt::AlignHCenter);
    filterTags = new QListView;
    filterTags->setParent(searchTags);

    outputNotes_n.setText("Résultat:");
    outputNotes_n.setParent(searchTags);
    outputNotes_n.setAlignment(Qt::AlignHCenter);
    outputNotes = new QListView;
    outputNotes->setParent(searchTags);
    //listes des notes mises à jours avec les tags (par défaut on affiche toutes les notes)
    outputNotes->addActions(notes);

    searchTags->layout()->addWidget(inputTags);
    searchTags->layout()->addWidget(&filterTags_n);
    searchTags->layout()->addWidget(filterTags);
    searchTags->layout()->addWidget(&outputNotes_n);
    searchTags->layout()->addWidget(outputNotes);

    //Séparation des éléments
    zone->setLayout(zoneLay);
    zone->layout()->addWidget(searchTags);
    //zone->layout()->addWidget(editorNote);
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

    //Menu Corbeille (lister les éléments suprimés en QAction (cliqued() => restaurer) + QAction "Vider la corbeille" + Qaction "tout restaurer"
    bin = menuBar()->addMenu("&Corbeille");

    bin->addActions(deleted);

    bin->addSeparator();

    binDel = new QAction("Vider la corbeille", this);
    bin->addAction(binDel);

    binRec = new QAction("Tout restaurer", this);
    bin->addAction(binRec);

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

    QObject::connect(mapper, SIGNAL(mapped(QObject*)), this, SLOT(openNote(QObject*)));
}

MainWindow::~MainWindow(){
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
   QAction* act = new QAction(ico_article, art->getTitle(), this);
   //printf("title = %s\n", art->getTitle().toStdString().c_str());
DEBUGP
    openNote(new ArticleEditor(art));
DEBUGP


    //connecte le nouvel object à l'ouverture de la note
    QObject::connect(act, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(act, editorNote);
    notes.push_back(act);
    qnotes.push_back(editorNote);

    //pour le moment ouvre un article déjà créé
    //QString note = QFileDialog::getOpenFileName(this);
    //QMessageBox::information(NULL, "Fichier(s) ouvert(s):", note, QMessageBox::Ok);
}

void MainWindow::imageCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Image* img = dynamic_cast<Image*>(&manager->getNewNote("Image", ""));
    QAction* act = new QAction(ico_image, img->getTitle(), this);
    openNote(new ImageEditor(img));

    //connecte le nouvel object à l'ouverture de la note
    QObject::connect(act, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(act, editorNote);
    notes.push_back(act);
    qnotes.push_back(editorNote);
}

void MainWindow::audioCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Audio *aud = dynamic_cast<Audio*>(&manager->getNewNote("Audio", ""));
    QAction* act = new QAction(ico_audio, aud->getTitle(), this);
    openNote(new AudioEditor(aud));

    //connecte le nouvel object à l'ouverture de la note
    QObject::connect(act, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(act, editorNote);
    notes.push_back(act);
    qnotes.push_back(editorNote);
}

void MainWindow::videoCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Video* vid = dynamic_cast<Video*>(&manager->getNewNote("Video", ""));
    QAction* act = new QAction(ico_video, vid->getTitle(), this);
    openNote(new VideoEditor(vid));

    //connecte le nouvel object à l'ouverture de la note
    QObject::connect(act, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(act, editorNote);
    notes.push_back(act);
    qnotes.push_back(editorNote);
}

void MainWindow::documentCreator(){
    //vérifier q'un workspace est ouvert sinon en ouvrir/créer un
    //si note en cours d'édition la fermer (demander de sauver + fermer)
    //Créer une nouvelle note si fermé avec succès
    Document* doc = dynamic_cast<Document*>(&manager->getNewNote("Document", ""));
    QAction* act = new QAction(ico_document, doc->getTitle(), this);
    openNote(new DocumentEditor(doc));

    //connecte le nouvel object à l'ouverture de la note
    QObject::connect(act, SIGNAL(triggered()), mapper, SLOT(map()));
    mapper->setMapping(act, editorNote);
    notes.push_back(act);
    qnotes.push_back(editorNote);
}

void MainWindow::openNote(QObject *o){
    editorNote = (NoteEditor*)o;

    zone->layout()->addWidget(editorNote);

    //passage des icon à visible
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
    manager->saveNote(editorNote->getRessource());
    save->setEnabled(false);
}

void MainWindow::deleteNote(){
    QAction *act = getAction(editorNote);
    //retire la note de la liste des notes
    notes.removeAll(act);
    //ajoute la note à la liste des supprimées
    deleted.push_back(act);
    zone->layout()->removeWidget(editorNote);
    editorNote = NULL;

    save->setEnabled(false);
    print->setEnabled(false);
    trash->setEnabled(false);
}

QAction* MainWindow::getAction(NoteEditor* n){
    return (QAction*)mapper->mapping((QObject*)n);
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
