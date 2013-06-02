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
