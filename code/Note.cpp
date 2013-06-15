#include "Note.h"

void Note::addSubNote(Note *n){throw NotesException("Bad using");}
void Note::addSubNote(Note *n, unsigned int pos){throw NotesException("Bad using");}
Note* Note::getSubNote(unsigned int pos){throw NotesException("Bad using");}
void Note::removeSubNote(unsigned int pos){throw NotesException("Bad using");}

QTextStream& operator<<(QTextStream& f, Note& n){
    return n.save(f);
}

NoteEditor::NoteEditor(Note* n, QWidget* parent):QWidget(parent){
    ressource = n;
    this->setParent(parent);

    html = new QLabel(n->toHTML());
    tex = new QLabel(n->toTEX());
    text = new QLabel(n->toTEXT());

    mainLay = new QVBoxLayout;
    this->setLayout(mainLay);

    tabs = new QTabWidget(this);
    this->layout()->addWidget(tabs);

//Intégrer à zone un scroll area
    zone = new QWidget(this);
    zoneLayout = new QVBoxLayout;
    zone->setLayout(zoneLayout);
    this->layout()->addWidget(zone);

    title = new QLineEdit;
    title->setText(n->getTitle());
    zone->layout()->addWidget(title);

    tabs->addTab(zone, "Editeur");
    tabs->addTab(html, "HTML");
    tabs->addTab(tex, "TEX");
    tabs->addTab(text, "Texte");

    //ouverture d'une tabulation => génération du code
    QObject::connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(tabed(int)));

}

void NoteEditor::tabed(int tab){
    /*if(tab == tabs->indexOf(html))
        html->setText(ressource->toHTML());
    else */if(tab == tabs->indexOf(tex))
        tex->setText(ressource->toTEX());
    else if(tab == tabs->indexOf(text))
        text->setText(ressource->toTEXT());
}

void Note::createHtmlTree(QBuffer* buf){
    QXmlStreamWriter qw;

    //Creation of the HTML architecture
    qw.setDevice(buf);
    qw.setAutoFormatting(true);
    qw.setAutoFormattingIndent(-1);
    qw.writeDTD("<!DOCTYPE html>");
        qw.writeStartElement("html");
            qw.writeStartElement("head");
                qw.writeEmptyElement("meta");
                qw.writeAttribute("charset","utf-8");
                qw.writeTextElement("title",this->getTitle());
                qw.writeEndElement();
            qw.writeStartElement("body");
}

void Note::endHtmlTree(QBuffer* buf){

    if (!buf->open(QIODevice::WriteOnly| QIODevice::Text| QIODevice::Truncate))
        throw NotesException("EndHtmlTree Buffer opening problem");

    QXmlStreamWriter qw;
    qw.setDevice(buf);
            qw.writeEndElement();
            qw.writeEndElement();
     qw.writeEndElement();
}

void Note::createTexHeader(QBuffer *buf){

    buf->write("\\documentclass[a4paper,11pt]{report} %type du document\n");

    buf->write("\\usepackage[french]{babel}");

    buf->write("\\usepackage[utf8]{inputenc}\n");

    buf->write("\\usepackage[T1]{fontenc}\n");
}
