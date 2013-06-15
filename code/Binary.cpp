#include "Binary.h"

BinaryEditor::BinaryEditor(Binary *b, QWidget *parent):NoteEditor(b, parent){
    desc = new QTextEdit;
    desc->setText(b->getDesc());
    zone->layout()->addWidget(desc);

    //Qlabel pour le lien et un bouton "..." à côté pour sélectionner un fichier
    pathZone = new QWidget;
    pathLay = new QHBoxLayout;
    path = new QLabel("File path: " + b->getPath());
    pathLay->addWidget(path);
    chPath = new QPushButton(ico_change, "Changer de fichier ...");
    pathLay->addWidget(chPath);
    pathZone->setLayout(pathLay);
    zone->layout()->addWidget(pathZone);

    //connecte le bouton à un slot de changement de fichier
    QObject::connect(desc, SIGNAL(textChanged()), this, SLOT(descMod()));
    QObject::connect(chPath, SIGNAL(clicked()), this, SLOT(changeFile()));
}

void BinaryEditor::descMod(){
    ((Binary*)ressource)->setDesc(desc->toPlainText());
}

void BinaryEditor::changeFile(){
    ((Binary*)ressource)->setPath(selectFile());
    path->setText(((Binary*)ressource)->getPath());
    updateBin();
}
