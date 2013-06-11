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
void Note::createHtmlTree(QBuffer* buf ){
    /* If problem during the acess of the QBuffer*/

    QXmlStreamWriter qw;

    //Creation of the HTML architecture
    qw.setDevice(buf);
    qw.setAutoFormatting(true);
    qw.setAutoFormattingIndent(-1);
    qw.writeDTD("<!xDOCTYPE xhtml>");
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
