#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Note.h"

///\class Document
///Correspond à la spécification de Note pour contenir:
///des sous-notes (Audio, Article, Image, Video)
///un type d'éditeur i.e. un graphisme spécifique
///et des exports HTML,Tex,TEXT correspondants

#include "NotesManager.h"
#include "MainWindow.h"

class QListEditor;
class QListEditorItem;


class DocButton:public QPushButton{
    Q_OBJECT
private:
    QWidget *widget;
public:
    DocButton(QWidget* wid, const QIcon& ico, const QString& txt, QWidget *p = NULL):QPushButton(ico, txt, p), widget(wid){}
    DocButton(QWidget* wid, const QString& txt, QWidget *p = NULL):QPushButton(txt, p), widget(wid){}

signals:
    void sendWid(QWidget*);
public slots:
    void getWid();
};

class Document: public Note{
private:
    std::list<Note*> content;
    void operator=(const Document&);
    Document(Document& d);
    void load();
public:
    Document(const QString& id, const QString& title, const std::list<Note*> content = std::list<Note*>()):Note("Document", id, title),content(content){}

    void addSubNote(Note* n);
    void addSubNote(Note *n, unsigned int);
    void removeSubNote(unsigned int);
    void removeSubNote(const Note*);
    Note* getSubNote(unsigned int pos);
    bool isNote(const Note*);
    bool isNote(const QString&);

    unsigned int getNbSubNotes() {return content.size();}
    QTextStream& save(QTextStream& f);
    NoteEditor* getEditor(QWidget *parent = NULL);

    virtual void makehtmlbody(QXmlStreamWriter* qw);
    QString toTEX();
    QString toTEXT();
};

class DocumentEditor: public NoteEditor{
Q_OBJECT
protected:
    std::list<QWidget*> content;
    QDialog *ask;
    QListEditor *notes;

public:
    DocumentEditor(Document* d, QWidget* parent = NULL);
    ~DocumentEditor(){}

    void insertNote(NoteEditor*, QWidget* parent = NULL);

public slots:
    void detachNote(QWidget*);
    void selectNote();
    void openNote(QListEditorItem*);
};

#endif // DOCUMENT_H

