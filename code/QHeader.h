#ifndef QHEADER_H
#define QHEADER_H

#include <fstream>
#include <list>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListView>
#include <QString>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

static QString APP_TITLE("BanaNotes");
static QString CREDITS("Application développée dans le cadre d'un projet de LO21 à l'UTC au printemps 2013.\n\nCrédits à Jonathan DIGUET et Marc-Antoine MARTIN.");

#endif // QHEADER_H
