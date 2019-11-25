//#include "mainwindow.h"
#include "authenticate.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Authenticate w;
    w.show();

    return a.exec();
}
