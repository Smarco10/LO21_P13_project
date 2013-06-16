﻿#ifndef CONFIG_H
#define CONFIG_H

#include "QHeader.h"
#include "MainWindow.h"
///\class Config
///Gère le fichier de configuration du programme avec:
///les différents Workspaces
///les opérations sur ceux-ci

///un Path( chemin d'accès)
///un type d'éditeur i.e. un graphisme spécifique
///
class Config{
private:
    QDomDocument *dom;
    bool modified;

public:
    Config();
    ~Config(){if(modified) updateConfig();}

    bool isWS(const QString&);
    unsigned int nbWS();
    QString lastWS();
    void updateLastWS(const QString&);

    void check();
    bool newWS(const QString&);
    bool cloneWS(const QString&, const QString&);
    void deleteWS(const QString&);

    void updateConfig();
    QList<QString> listWS();
};

class ConfigManager:public QDialog{
    Q_OBJECT
private:
    Config *conf;
    QString pathWS;

    QVBoxLayout *altWindowLay;

    QLabel *info;

    QWidget *listes;
    QHBoxLayout *listesLay;

    QWidget *buttons;
    QHBoxLayout *buttonsLay;

    QPushButton *open;
    QPushButton *clone;
    QPushButton *del;
    QPushButton *create;

    QListWidget *workspaces;
    QLabel *notes;

public:
    ConfigManager(QWidget *parent=NULL);
    ~ConfigManager(){delete conf;}

    QString getPath() const {return pathWS;}
    void updateGUI();

public slots:
    void safeDel();
    void delWS();
    void newWS();
    void cloneWS();
    void loadWS();
    void showNotes(QListWidgetItem*);
};

#endif // CONFIG_H
