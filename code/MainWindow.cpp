#include "MainWindow.h"

MainWindow::MainWindow(QApplication* app){
    //manager = &NotesManager::getInstance();

    /*zone = new QWidget;
    zoneLay = new QHBoxLayout;
    zone->setLayout(zoneLay);
    setCentralWidget(zone);

    tbarMisc = addToolBar("Miscellaneous");
    tbarOpen = addToolBar("OpenElements");

    fichier = menuBar()->addMenu("&Fichier");

    ouvrir = fichier->addMenu("&Ouvrir");
    quitter = new QAction(QIcon("icons/quitter.png"), "Quitter", this);
    fichier->addAction(quitter);
    tbarMisc->addAction(quitter);

    article = new QAction(QIcon("icons/article.png"), "Article(s)", this);
    ouvrir->addAction(article);
    tbarOpen->addAction(article);

    image = new QAction(QIcon("icons/image.png"), "Image(s)", this);
    ouvrir->addAction(image);
    tbarOpen->addAction(image);

    audio = new QAction(QIcon("icons/audio.png"), "Enregistrement(s) Audio", this);
    ouvrir->addAction(audio);
    tbarOpen->addAction(audio);

    video = new QAction(QIcon("icons/video.png"), "Enregistrement(s) Video", this);
    ouvrir->addAction(video);
    tbarOpen->addAction(video);

    document = new QAction(QIcon("icons/document.png"), "Document(s)", this);
    ouvrir->addAction(document);
    tbarOpen->addAction(document);


    QObject::connect(article, SIGNAL(triggered()), this, SLOT(articleEditor()));
    QObject::connect(image, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(audio, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(video, SIGNAL(triggered()), this, SLOT(warning()));
    QObject::connect(document, SIGNAL(triggered()), this, SLOT(warning()));

    QObject::connect(quitter, SIGNAL(triggered()), app, SLOT(quit()));*/
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
    QMessageBox::warning(NULL, "Fichier(s) ouvert(s):", note, QMessageBox::Ok);

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
