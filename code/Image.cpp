#include "Image.h"

void Image::load(){
    //récupère les information pouvant manquer
    QFile fichier(getWS() + getId());

    //on sort si le fichier n'existe pas
    if(!fichier.exists())
        return;

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

QTextStream& Image::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getPath()<<"\n";
    f<<this->getDesc()<<"\n";
    return f;
}

QString Image::toHTML(){
    QXmlStreamWriter* qw=new QXmlStreamWriter;


    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }
    createHtmlTree(buffer);

    qw->setDevice(buffer);
    qw->writeEmptyElement("br");
    qw->writeTextElement("h1",QString("Titre:")+this->getTitle());
    qw->writeTextElement("h2",QString("ID:")+this->getId());
    qw->writeTextElement("h3",QString("PATH:")+this->getPath());
    qw->writeStartElement("img");
            qw->writeAttribute("source",this->getPath());
    qw->writeEndElement();
    qw->writeTextElement("p",this->getDesc());
    //qw->writeTextElement("p",QString("Tag:")+(*it).getTags());
    qw->writeEmptyElement("br");


    endHtmlTree(buffer);
    buffer->close();
    return QString(*file);
}

QString Image::toTEX(){
    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
         throw NotesException("Buffer unavailable for HTML export.");
     }
    createTexHeader(buffer);
    buffer->write("\\usepackage{graphicx}");
    buffer->write("\\begin{document}\n");
    buffer->write(("\\chapter{"+this->getTitle()+"}\n").toAscii());
    buffer->write(("{\Large ID:"+this->getId()+"}\n").toAscii());
    buffer->write(("\\includegraphics{"+this->getPath()).toAscii());
    buffer->write(("\\paragraph{PATH:"+this->getPath()+"}"+this->getDesc()+"\n").toAscii());
    buffer->write("\\end{document}");
    buffer->close();
    return QString(*file);
}


QString Image::toTEXT(){
    return "";
}

ImageEditor::ImageEditor(Image *i, QWidget *parent):BinaryEditor(i, parent){
    image = new QLabel(parent);
    image->setPixmap(QPixmap(i->getPath()));
    zone->layout()->addWidget(image);
}

void ImageEditor::update(QString s){

}
