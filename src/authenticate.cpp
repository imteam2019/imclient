#include "authenticate.h"
#include "mainwindow.h"
#include "ui_authenticate.h"

Authenticate::Authenticate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authenticate)
{
    ui->setupUi(this);
}

Authenticate::~Authenticate()
{
    delete ui;
}

void Authenticate::on_btnOK_clicked()
{
    MainWindow *mw=new MainWindow;
    mw->show();
    this->close();

}
