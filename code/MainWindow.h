#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QHeader.h"
#include "NotesManager.h"

//Faire un fichier de config où l'on stock les valeurs du fichier ressources.h
//ainsi que le path par défaut qui est le dernier utilisé dans l'applis

class MainWindow:public QMainWindow{
    Q_OBJECT
private:
    QWidget *zone;

    NoteEditor *editorNote;
    QWidget *searchTags;

    QVBoxLayout *tagsLay;
    QHBoxLayout *zoneLay;

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

    QMenu *edit;

    QSignalMapper *mapper;

    //Corbeille
    QMenu *bin;
    QAction *binDel;
    QAction *binRec;
    QList<QAction*> deleted;

    QMenu *help;
    QAction *about;

    //Partie searchTags
    QLineEdit *inputTags;
    QLabel filterTags_n;
    QListView *filterTags;
    QLabel outputNotes_n;
    QListView *outputNotes;

    QList<QAction*> notes;

    QList<NoteEditor*> qnotes;

    NotesManager *manager;

    QAction* getAction(NoteEditor*);

public:
    MainWindow(QApplication*);
    ~MainWindow();

private slots:
    void warning();
    void aboutApp();

    void articleCreator();
    void imageCreator();
    void audioCreator();
    void videoCreator();
    void documentCreator();

    void openNote(QObject*);
    void printNote();
    void saveNote();
    void deleteNote();
};

#endif // MAINWINDOW_H
