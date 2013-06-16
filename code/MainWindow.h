#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QHeader.h"
#include "NotesManager.h"
#include "Note.h"
#include "Config.h"
///classe MainWindow
///Gère la création de l'interface Graphique, les liens entre les différents
///menus ou widgets et les fonctions relatives.
///

//Faire un fichier de config où l'on stock les valeurs du fichier ressources.h
//ainsi que le path par défaut qui est le dernier utilisé dans l'applis

class QListEditorItem:public QAction{
    NoteEditor *ressource;
public:
    QListEditorItem(const QString& tt, NoteEditor* res, QObject* parent=NULL):QAction(tt, parent),ressource(res){}
    QListEditorItem(const QIcon& ico, NoteEditor* res, QObject* parent=NULL):QAction(ico, "", parent),ressource(res){}
    QListEditorItem(const QIcon& ico, const QString& tt, NoteEditor* res, QObject* parent=NULL):QAction(ico, tt, parent),ressource(res){}
    ~QListEditorItem(){}

    NoteEditor* getRessource() const {return ressource;}
};

class QListEditor: public QListWidget{
    Q_OBJECT
private:
    QList<QListEditorItem*> editors;
    QVBoxLayout *lay;

public:
    QListEditor(QWidget* parent=NULL):QListWidget(parent){}
    ~QListEditor(){}

    void addItem(QListEditorItem* itAct){QListWidgetItem *item = new QListWidgetItem(itAct->icon(), itAct->text(), this);
                                         this->QListWidget::addItem(item);
                                         editors.push_back(itAct);}
    QListEditorItem* takeItem(int pos){this->QListWidget::takeItem(pos);
                                       QListEditorItem *itAct = editors.at(pos);
                                       editors.removeAt(pos); return itAct;}
    void setCurrentItem(QListEditorItem *item){int pos = editors.indexOf(item); this->QListWidget::setCurrentItem(this->QListWidget::item(pos));}
    void clear() {this->QListWidget::clear(); editors.clear();}
    QListEditorItem* item(int pos) {return editors.at(pos);}

signals:
    void itActClickedS(QListEditorItem*);
    void itActDoubleClickedS(QListEditorItem*);

public slots:
    void itActClicked(QListWidgetItem *it){emit itActClickedS(this->item(this->row(it)));}
    void itActDoubleClicked(QListWidgetItem *it){emit itActDoubleClickedS(this->item(this->row(it)));}
};

class MainWindow:public QMainWindow{
    Q_OBJECT
private:
    QWidget *zone;

    QWidget *editor;
    QListEditorItem *editorNote;
    QWidget *searchTags;

    QHBoxLayout *zoneLay;
    QVBoxLayout *tagsLay;
    QVBoxLayout *editorLay;

    QToolBar *tbarOpen;
    QToolBar *tbarMisc;

    QMenu *file;
    QMenu *create;
    QAction *article;
    QAction *image;
    QAction *audio;
    QAction *video;
    QAction *document;
    QAction *print;
    QAction *save;
    QAction *quit;
    QAction *trash;
    QAction *changeWS;

    QMenu *exports;
    QAction *expHTML;
    QAction *expTeX;
    QAction *expText;

    QMenu *help;
    QAction *about;

    //Partie searchTags
    QLineEdit *inputTags;
    QLabel filterTags_n;
    QListEditor *filterTags;

    QTabWidget *tabs;
        //Onglet Résultats
    QListEditor *outputNotes;
        //Onglet Corbeille
    QWidget *bin;
    QListEditor *deleted;
    QPushButton *binDel;

    NotesManager *manager;

public:
    MainWindow(QApplication*);
    ~MainWindow();

    void noteCreator(Note *);
    QListEditorItem* newItem(Note*);

private slots:
    void warning();
    void aboutApp();

    void articleCreator();
    void imageCreator();
    void audioCreator();
    void videoCreator();
    void documentCreator();

    void updateNotes();

    void openNote(QListEditorItem*);
    void printNote();
    void saveNote();
    void deleteNote();
    void recoverNote(QListEditorItem*);
    void safeEmptyBin();
    void emptyBin();
    void changeWorkspace();

    void exportHTML();
    void exportTeX();
    void exportText();
};

#endif // MAINWINDOW_H
