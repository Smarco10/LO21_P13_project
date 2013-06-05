#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QHeader.h"

//Faire un fichier de config où l'on stock les valeurs du fichier ressources.h
//ainsi que le path par défaut qui est le dernier utilisé dans l'applis

class MainWindow:public QMainWindow{
    Q_OBJECT
private:
    QWidget *zone;

    QWidget *editorNote;    
    QWidget *searchTags;

    QVBoxLayout *tagsLay;
    QHBoxLayout *zoneLay;

    QToolBar *tbarOpen;
    QToolBar *tbarMisc;



    QMenu *file;
    QMenu *open;
    QAction *article;
    QAction *image;
    QAction *audio;
    QAction *video;
    QAction *document;
    QAction *print;
    QAction *save;
    QAction *quit;

    QMenu *edit;
    QMenu *view;

    QMenu *help;
    QAction *about;

    //Partie searchTags
    QLineEdit *inputTags;
    QLabel filterTags_n;
    QListView *filterTags;
    QLabel outputNotes_n;
    QListView *outputNotes;

    //NotesManager *manager;

public:
    MainWindow(QApplication*);
    ~MainWindow();

private slots:
    void warning();
    void noteEditor();
    void aboutApp();
};

#endif // MAINWINDOW_H
