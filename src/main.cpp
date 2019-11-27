//#include "mainwindow.h"
#include "authenticate.h"
#include "settingsglobal.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SettingsGlobal *sg=new SettingsGlobal();
    Authenticate w;
    w.show();
    return a.exec();
}
