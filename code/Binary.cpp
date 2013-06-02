#include "Binary.h"

BinaryEditor::BinaryEditor(Binary *b, QWidget *parent):NoteEditor(b, parent){
    desc = new QTextEdit;
    desc->setText(b->getDesc());
    zone->layout()->addWidget(desc);

    path = new QPushButton(b->getPath());
    zone->layout()->addWidget(path);

    //connecter le bouton à un slot de changement d'ouverture de fichier
}
