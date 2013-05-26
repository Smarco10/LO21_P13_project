#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QHeader.h"

class MainWindow:public QMainWindow{
    Q_OBJECT
private:
    QWidget *editeur;
    QWidget *searchTags;

    QVBoxLayout *tagsLay;

    QToolBar *tbarOpen;
    QToolBar *tbarMisc;

    QMenu *fichier;
    QMenu *ouvrir;

    QAction *quitter;
    QAction *article;
    QAction *image;
    QAction *audio;
    QAction *video;
    QAction *document;

    QAction *articleI;
    QAction *imageI;
    QAction *audioI;
    QAction *videoI;
    QAction *documentI;

    //NotesManager *manager;

public:
    MainWindow(QApplication*);
    ~MainWindow();

private slots:
    void warning();
    void noteEditor();
};

#endif // MAINWINDOW_H
