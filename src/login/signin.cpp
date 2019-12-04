#include "signin.h"
#include "mainwindow.h"
#include "ui_signin.h"

Signin::Signin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
}

Signin::~Signin()
{
    delete ui;
}

void Signin::on_btnOK_clicked()
{
    MainWindow *mw=new MainWindow;
    mw->show();
    this->close();

}
