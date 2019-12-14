#include "signin.h"

#include "mainwindow.h"
#include "signup.h"
#include "ui_signin.h"

Signin::Signin(QWidget *parent) : QDialog(parent), ui(new Ui::Signin) {
  ui->setupUi(this);
}

Signin::~Signin() { delete ui; }

bool Signin::login(QString strLoginInfo) {
  // todo

  return false;
}
void Signin::on_pbCancel_clicked() { this->close(); }

void Signin::on_pbOk_clicked() {
  QString strLoginInfo;
  // todo 验证用户身份

  if (this->login(strLoginInfo)) {
    MainWindow *w = new MainWindow();
    w->show();
    this->close();
  } else {
    ui->lePasswd->setFocus();
  }
}

void Signin::on_pbSignup_clicked() {
  Signup *su = new Signup;
  su->show();
  this->close();
}
