#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QHeader.h"

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
