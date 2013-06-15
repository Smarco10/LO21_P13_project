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

void Note::createHtmlTree(QBuffer* buf ){


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
/*
\documentclass[a4paper,11pt]{report} %type du document
% Imports de bibliothèques
\usepackage{graphicx} %utilisé pour inclure des images
%gestion de la police
\usepackage[french]{babel}
\usepackage[latin1]{inputenc}
\usepackage[T1]{fontenc}
\begin{document}
\chapter{titre de niveau du chapitre}
\section{niveau 2}
Il faut écrire un fichier source et ensuite le compiler pour obtenir un fichier
PDF.
\subsection{niveau 3}
\subsubsection{niveau 4}
\paragraph{paragraphe titré} contenu de mon paragraphe.
%Ajout d’image
\begin{center}
\includegraphics{monImage.png}
\end{center}
\end{document}
*/
void Note::createTexHeader(QBuffer *buf){
    buffer->write("\\documentclass[a4paper,11pt]{report} %type du document\n");
    buffer->write("\\usepackage[french]{babel}");
    buffer->write("\\usepackage[utf8]{inputenc}\n");
    buffer->write("\\usepackage[T1]{fontenc}\n");


}
