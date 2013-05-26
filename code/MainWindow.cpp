#include "MainWindow.h"

MainWindow::MainWindow(QApplication* app){
    //manager = &NotesManager::getInstance();

    setWindowTitle(APP_TITLE);

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

    filterTags_n.setText("Filtres");
    filterTags_n.setParent(searchTags);
    filterTags = new QListView;
    filterTags->setParent(searchTags);

    outputNotes_n.setText("Filtres");
    outputNotes_n.setParent(searchTags);
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
    quit = new QAction(QIcon("icons/quitter.png"), "Quitter", this);
    file->addAction(quit);
    tbarMisc->addAction(quit);

    article = new QAction(QIcon("icons/article.png"), "Article(s)", this);
    open->addAction(article);
    tbarOpen->addAction(article);

    image = new QAction(QIcon("icons/image.png"), "Image(s)", this);
    open->addAction(image);
    tbarOpen->addAction(image);

    audio = new QAction(QIcon("icons/audio.png"), "Enregistrement(s) Audio", this);
    open->addAction(audio);
    tbarOpen->addAction(audio);

    video = new QAction(QIcon("icons/video.png"), "Enregistrement(s) Video", this);
    open->addAction(video);
    tbarOpen->addAction(video);

    document = new QAction(QIcon("icons/document.png"), "Document(s)", this);
    open->addAction(document);
    tbarOpen->addAction(document);

    //Menu Edition
    edit = menuBar()->addMenu("&Edition");

    //Menu Affichage
    view = menuBar()->addMenu("&Affichage");

    //Menu Aide
    help = menuBar()->addMenu("&Aide");
    about = new QAction("A propos de " + QString(APP_TITLE), this);
    help->addAction(about);

    //lien des menus
    QObject::connect(article, SIGNAL(triggered()), this, SLOT(noteEditor()));
    QObject::connect(image, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(audio, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(video, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(document, SIGNAL(triggered()), this, SLOT(warning()));

    QObject::connect(about, SIGNAL(triggered()), this, SLOT(aboutApp()));

    QObject::connect(quit, SIGNAL(triggered()), app, SLOT(quit()));
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
    //Afficher le logo en gros avec les crédit à côté genre Google Chrome
    QMessageBox::information(NULL, "A propos de " + APP_TITLE, CREDITS, QMessageBox::Accepted);
}
