#include "QHeader.h"
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    /*QPushButton bt("Quitter");
    bt.show();

    QObject::connect(&bt, SIGNAL(clicked()), &app, SLOT(quit()));
*/
    MainWindow wd(&app);
    wd.show();

    return app.exec();
}
