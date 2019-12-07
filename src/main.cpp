//#include "mainwindow.h"
#include "login/signup.h"
#include "login/signin.h"
#include "common/data.h"
#include "common/encrypt.h"

#include <QApplication>

int main(int argc, char *argv[])
{
   // Encrypt::getMD5(Encrypt::getRandKey().toLocal8Bit());


    QApplication a(argc, argv);
    Signup w;
    w.show();
    return a.exec();

}
