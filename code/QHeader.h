﻿#ifndef QHEADER_H
#define QHEADER_H
///Fichier contenant toutes les inclusions nécessaires au fonctionnement du programme
#include <fstream>
#include <list>
#include <set>
#include <typeinfo>

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
#include <QTextCodec>
#include <QDateTime>
#include <QtXml>
#include <QDomElement>
#include <QDomDocument>
#include <QList>
#include <QListWidget>
#include <QListWidgetItem>

class NotesManager;
class NoteEditor;


#define DEBUGP printf("\n%s: %d\n", __FILE__, __LINE__);

class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};

#include "ressources.h"

#endif // QHEADER_H
