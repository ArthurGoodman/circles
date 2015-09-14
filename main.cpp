#include "mainwidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWidget *w = new MainWidget;
    w->show();

    return a.exec();
}
