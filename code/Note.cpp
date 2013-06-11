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
}

void NoteEditor::modified(QString s){

}

void NoteEditor::modified(){

}
<<<<<<< HEAD
void Note::createHtmlTree(QBuffer* buf ){
=======

void Note::createHtmlTree(){
>>>>>>> 9c6bb3b2bfe54891bfec9d4cead12caeb6b1f349
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
