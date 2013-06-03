#include "Video.h"

void Video::load(){
    //récupère les information pouvant manquer
    QFile fichier(getId());
    if(!fichier.open(QIODevice::ReadOnly | QIODevice::Text)){
        throw NotesException("Can't open document file");
    }

     QTextStream flux(&fichier);
     //saute la première ligne
     flux.readLine();
     //récupère le chemin du fichier binaire associé
     if(!flux.atEnd())
        path = flux.readLine();
     //récupère la description du fichier
     while(!flux.atEnd())
         desc += flux.readLine();
}

QTextStream& Video::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}

QString Video::toHTML(){
    return "";
}

QString Video::toTEX(){
    return "";
}

QString Video::toTEXT(){
    return "";
}

VideoEditor::VideoEditor(Video *v, QWidget *parent):BinaryEditor(v, parent){
    movie = new QMovie(path);
    frame = new QLabel(parent);
    //frame->setPixmap(QPixmap());

    zone->layout()->addWidget(frame);

    control = new QWidget;
    controlLay = new QHBoxLayout;

    //changer le nom du bouton et le passer à pause quand la lecture est lancée
    play_bt = new QPushButton("lecture");
    stop_bt = new QPushButton("stop");

    controlLay->addWidget(play_bt);
    controlLay->addWidget(stop_bt);
    control->setLayout(controlLay);
    zone->layout()->addWidget(control);

    //connecter play_bt et stop_bt à movie
    QObject::connect(play_bt, SIGNAL(clicked()), movie, SLOT(start()));
    QObject::connect(stop_bt, SIGNAL(clicked()), movie, SLOT(stop()));
    //récupérer l'image courante et la mettre à jour
    //QObject::connect(movie, SIGNAL(frameChanged(int)), , SLOT());
}

void VideoEditor::update(QString s){

}
