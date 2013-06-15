#ifndef CONFIG_H
#define CONFIG_H

#include "QHeader.h"
#include "MainWindow.h"

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
    ConfigManager(QApplication*, QWidget *parent=NULL);
    ~ConfigManager(){delete conf;}

    QString getPath() const {return pathWS;}
    void updateGUI();

signals:
    void quitS();

public slots:
    void safeDel();
    void delWS();
    void quit(int);
    void newWS();
    void cloneWS();
    void loadWS();
    void showNotes(QListWidgetItem*);
};

#endif // CONFIG_H
