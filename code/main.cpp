#include "QHeader.h"
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);

    MainWindow wd(&app);
    wd.show();

    return app.exec();
}
