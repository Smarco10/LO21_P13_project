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
    /*area = new QScrollArea(this);
    this->layout()->addWidget(area);*/

    zone = new QWidget(this);
    zoneLayout = new QVBoxLayout;
    zone->setLayout(zoneLayout);
    this->layout()->addWidget(zone);
    //area->setWidget(zone);

    title = new QLineEdit;
    title->setText(n->getTitle());
    zone->layout()->addWidget(title);

    tabs->addTab(zone, "Editeur");
    tabs->addTab(html, "HTML");
    tabs->addTab(tex, "TeX");
    tabs->addTab(text, "Texte");

    QObject::connect(title, SIGNAL(textChanged(QString)), this, SLOT(titleMod(QString)));

    //ouverture d'une tabulation => génération du code
    QObject::connect(tabs, SIGNAL(currentChanged(int)), this, SLOT(tabed(int)));
}

void NoteEditor::titleMod(QString tt){
    ressource->setTitle(tt);
}

void NoteEditor::tabed(int tab){
    if(tab == tabs->indexOf(html))
        html->setText(ressource->toHTML());
    else if(tab == tabs->indexOf(tex))
        tex->setText(ressource->toTEX());
    else if(tab == tabs->indexOf(text))
        text->setText(ressource->toTEXT());
}

void Note::createTexHeader(QBuffer *buf){

    buf->write("\\documentclass[a4paper,11pt]{report} %type du document\n");

    buf->write("\\usepackage[french]{babel}");

    buf->write("\\usepackage[utf8]{inputenc}\n");

    buf->write("\\usepackage[T1]{fontenc}\n");
}
QString Note::toHTML(){
    QXmlStreamWriter* qw=new QXmlStreamWriter;

    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }

    qw->setDevice(buffer);
    qw->setAutoFormatting(true);
    qw->setAutoFormattingIndent(-1);
    qw->writeDTD("<!DOCTYPE html>");
    qw->writeStartElement("html");
        qw->writeStartElement("head");
            qw->writeEmptyElement("meta");
            qw->writeAttribute("charset","utf-8");
            qw->writeTextElement("title",this->getTitle());
        qw->writeEndElement();
        qw->writeStartElement("body");
            this->makehtmlbody(qw);
        qw->writeEndElement();
    qw->writeEndElement();
    buffer->close();
    return QString(*file);
}
