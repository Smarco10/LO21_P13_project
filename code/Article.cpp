#include "Article.h"

void Article::load(){
    //Si la note est déjà chargée on ne le recharge pas
    if(getLoaded())
        return;

    //récupère les information pouvant manquer comme le contenu
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
     //récupère tout le contenu
     while(!flux.atEnd())
        content += flux.readLine();

     setLoaded(true);
}

QTextStream& Article::save(QTextStream& f){
    f<<this->getTitle()<<"\n";
    f<<this->getContent()<<"\n";
    return f;
}

QString Article::toHTML(){
    QXmlStreamWriter* qw=new QXmlStreamWriter;

   if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
        throw NotesException("Buffer unavailable for HTML export.");
    }
    createHtmlTree(buffer);
    qw->setDevice(buffer);
    qw->writeTextElement("h1",QString("Titre:")+this->getTitle());
    qw->writeTextElement("h2",QString("ID:")+this->getId());
    qw->writeTextElement("p",this->getContent());
    //qw->writeTextElement("p",QString("Tag:")+this->getTags());
    endHtmlTree(buffer);
    buffer->close();
    return QString(*file);
}


QString Article::toTEX(){

    if (!buffer->open(QIODevice::WriteOnly |QIODevice::Truncate)) {
         throw NotesException("Buffer unavailable for HTML export.");
     }
    createTexHeader(buffer);
    buffer->write("\\begin{document}\n");
    buffer->write((QString("\\chapter{")+this->getTitle()+QString("}\n")).toAscii());
    buffer->write((QString("{\Large ID:")+this->getId()+QString("}\n")).toAscii());
    buffer->write((QString("\\paragraph{}")+this->getContent()).toAscii());
    buffer->write("\\end{document}");
    buffer->close();

    return QString(*file);
}

QString Article::toTEXT(){
    return "";
}

ArticleEditor::ArticleEditor(Article* a, QWidget* parent):NoteEditor(a, parent){
    content = new QTextEdit;
    content->setText(a->getContent());

    zone->layout()->addWidget(content);
}

void ArticleEditor::update(QString s){

}


