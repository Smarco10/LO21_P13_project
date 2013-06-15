#include "Image.h"

void Image::load(){
    if(getLoaded())
        return;

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

     setLoaded(true);
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

    //Creation of the HTML architecture
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
            qw->writeEmptyElement("br");
            qw->writeTextElement("h1",this->getTitle());
            qw->writeEmptyElement("br");
            qw->writeEmptyElement("br");
            qw->writeTextElement("h3",QString("PATH: ")+this->getPath());
            qw->writeEmptyElement("br");
            qw->writeEmptyElement("br");
            qw->writeStartElement("img");
                qw->writeAttribute("source",this->getPath());
            qw->writeEndElement();
            qw->writeEmptyElement("br");
            qw->writeTextElement("p",this->getDesc());
            qw->writeEmptyElement("br");
            //qw->writeTextElement("p",QString("Tag:")+(*it).getTags());
        qw->writeEndElement();
    qw->writeEndElement();
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

    buffer->write(("\\includegraphics{"+this->getPath()).toAscii() + "}\n");

    buffer->write(("\\paragraph{PATH:"+this->getPath()+"}"+this->getDesc()+"\n").toAscii());
    buffer->write("\\end{document}");
    buffer->close();
    return QString(*file);
}


QString Image::toTEXT(){
    return getTitle() + "\n\nChemin du fichier: " + getPath() + "\n\nDesciption du fichier: " + getDesc();
}

ImageEditor::ImageEditor(Image *i, QWidget *parent):BinaryEditor(i, parent){   
    image = new QLabel(parent);
    image->setPixmap(QPixmap(i->getPath()));
    zone->layout()->addWidget(image);
}

QString ImageEditor::selectFile(){
    return QFileDialog::getOpenFileName(NULL, "Selectionner une image", QDir::homePath(), "*.bmp *.gif *.jpg *.jpeg *.png *.pbm *.pgm *.ppm *.tiff  *.xbm *.xpm");
}

void ImageEditor::updateBin(){
    image->setPixmap(QPixmap(((Binary*)ressource)->getPath()));
}
