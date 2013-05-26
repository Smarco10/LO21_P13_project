#ifndef QHEADER_H
#define QHEADER_H

#include <fstream>
#include <list>

#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QString>
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

#endif // QHEADER_H
