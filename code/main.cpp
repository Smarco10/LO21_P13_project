#include "QHeader.h"
#include <QPushButton>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    QPushButton bt("Quitter");
    bt.show();

    QObject::connect(&bt, SIGNAL(clicked()), &app, SLOT(quit()));

    return app.exec();
}
