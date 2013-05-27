#ifndef QHEADER_H
#define QHEADER_H

#include <fstream>
#include <list>

#include <QApplication>
#include <QtGui>
#include <QMainWindow>
#include <QDialog>
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

QString::fromUtf8("éèçàù");

#include "ressources.h"

#endif // QHEADER_H
