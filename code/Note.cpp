#include "Note.h"

void Note::addSubNote(Note *n){throw NotesException("Bad using");}
void Note::addSubNote(Note *n, unsigned int pos){throw NotesException("Bad using");}
Note* Note::getSubNote(unsigned int pos){throw NotesException("Bad using");}
void Note::removeSubNote(unsigned int pos){throw NotesException("Bad using");}

QTextStream& operator<<(QTextStream& f, Note& n){
    return n.save(f);
}


NoteEditor::NoteEditor(Note* n, QWidget* parent){
    ressource = n;
    this->setParent(parent);

    html = new QLabel(n->toHTML());
    tex = new QLabel(n->toTEX());
    text = new QLabel(n->toTEXT());

    tabs = new QTabWidget(parent);
    tabs->addTab(this, "Editeur");
    tabs->addTab(html, "HTML");
    tabs->addTab(tex, "TEX");
    tabs->addTab(text, "Texte");

    area = new QScrollArea(this);
    zone = new QWidget(area);
    area->setWidget(zone);
    area->ensureWidgetVisible(zone);
    zoneLayout = new QVBoxLayout();
    zone->setLayout(zoneLayout);

    title = new QLineEdit(this);
    title->setText(n->getTitle());
    zone->layout()->addWidget(title);
}

void NoteEditor::modified(QString s){

}

void NoteEditor::modified(){

}
void Note::createHtmlTree(){
    /* If problem during the acess of the QBuffer*/
    if (!buffer->open(QIODevice::WriteOnly| QIODevice::Text| QIODevice::Truncate))
        throw NotesException("CreateHtmlTree Buffer opening problem");

    QXmlStreamWriter* qw=new QXmlStreamWriter;

    //Creation of the HTML architecture
    qw->setDevice(buffer);
    qw->setAutoFormatting(true);
    qw->setAutoFormattingIndent(-1);
    qw->writeStartElement("!xDOCTYPE HTML");
        qw->writeStartElement("xhtml");
            qw->writeStartElement("head");
                qw->writeEmptyElement("meta");
                qw->writeAttribute("charset","utf-8");
                qw->writeStartElement("title");
                qw->writeCharacters("me gusta la banana");
                qw->writeEndElement();
            qw->writeEndElement();
            qw->writeStartElement("body");
            qw->writeEndElement();
            qw->writeEndElement();
    qw->writeEndElement();
    buffer->close();
    delete qw;

}
