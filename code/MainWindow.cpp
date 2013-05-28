#include "MainWindow.h"

MainWindow::MainWindow(QApplication* app){
    //manager = &NotesManager::getInstance();

    setWindowTitle(APP_TITLE);
    setWindowIcon(QIcon(APP_LOGO));

    zone = new QWidget;
    editorNote = new QWidget;
    searchTags = new QWidget;

    tagsLay = new QVBoxLayout;
    zoneLay = new QHBoxLayout;

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

    searchTags->layout()->addWidget(inputTags);
    searchTags->layout()->addWidget(&filterTags_n);
    searchTags->layout()->addWidget(filterTags);
    searchTags->layout()->addWidget(&outputNotes_n);
    searchTags->layout()->addWidget(outputNotes);

    //Séparation des éléments
    zone->setLayout(zoneLay);
    zone->layout()->addWidget(searchTags);
    zone->layout()->addWidget(editorNote);
    setCentralWidget(zone);

    //Menu
    tbarMisc = addToolBar("Miscellaneous");
    tbarOpen = addToolBar("OpenElements");

    //Menu Fichier
    file = menuBar()->addMenu("&Fichier");

    open = file->addMenu("&Ouvrir");

    save = new QAction(ico_save, "Sauver", this);
    save->setDisabled(true);
    file->addAction(save);
    tbarMisc->addAction(save);

    print = new QAction(ico_print, "Imprimer", this);
    print->setDisabled(true);
    file->addAction(print);
    tbarMisc->addAction(print);

    quit = new QAction(ico_quit, "Quitter", this);
    file->addAction(quit);
    tbarMisc->addAction(quit);

    article = new QAction(ico_article, "Article(s)", this);
    open->addAction(article);
    tbarOpen->addAction(article);

    image = new QAction(ico_image, "Image(s)", this);
    open->addAction(image);
    tbarOpen->addAction(image);

    audio = new QAction(ico_audio, "Enregistrement(s) Audio", this);
    open->addAction(audio);
    tbarOpen->addAction(audio);

    video = new QAction(ico_video, "Enregistrement(s) Video", this);
    open->addAction(video);
    tbarOpen->addAction(video);

    document = new QAction(ico_document, "Document(s)", this);
    open->addAction(document);
    tbarOpen->addAction(document);

    //Menu Edition
    edit = menuBar()->addMenu("&Edition");

    //Menu Affichage
    view = menuBar()->addMenu("&Affichage");

    //Menu Aide
    help = menuBar()->addMenu("&Aide");
    about = new QAction("À propos de " + APP_TITLE, this);
    help->addAction(about);

    //lien des menus
    QObject::connect(article, SIGNAL(triggered()), this, SLOT(noteEditor()));
    QObject::connect(image, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(audio, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(video, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(document, SIGNAL(triggered()), this, SLOT(warning()));

    QObject::connect(save, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(print, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(quit, SIGNAL(triggered()), app, SLOT(quit()));

    QObject::connect(about, SIGNAL(triggered()), this, SLOT(aboutApp()));
}

MainWindow::~MainWindow(){
    //NotesManager::libererInstance();
}

void MainWindow::warning(){
    QMessageBox::warning(NULL, "Attention", "Ce menu n'est pas encore implémenté", QMessageBox::Ok);
}

void MainWindow::noteEditor(){
    //QString article = QFileDialog::getOpenFileName(this);

    //Permet d'ouvrir plusieurs fichiers en même temps
    QString note = QFileDialog::getOpenFileName(this);
    QMessageBox::information(NULL, "Fichier(s) ouvert(s):", note, QMessageBox::Ok);

    /*for(QStringList::iterator i = articles.begin(); i != articles.end(); i++){
        Article& art = manager->getArticle(*i);

        QWidget *art_buff = new ArticleEditeur(&art, zone);*/

 //vérifier que l'article n'a pas déjà été ouvert sinon l'ajouter (vérifier que l'object ressource associé ne fait pas déjà partie de la liste des ressources associées aux objects)
        /*int j;
        for(j = 0; j < zone->layout()->count(); j++)
            if(QString(zone->layout()->itemAt(j)->widget() != 0 && typeid(zone->layout()->itemAt(j)->widget()).name()).contains("ArticleEditeur"))
                if(((ArticleEditeur*)zone->layout()->itemAt(j)->widget())->isRessource(&art))
                        break;
        if(j == zone->layout()->count())*/

       // zone->layout()->addWidget(((ArticleEditeur*)art_buff)->onglets);

        //QMessageBox::information(NULL, art.getTitle(), typeid(art).name(), QMessageBox::Ok);
    //}
}

void MainWindow::aboutApp(){
    //Afficher le logo en gros avec les crédits à côté genre Google Chrome

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
