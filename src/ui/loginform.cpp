#include "loginform.h"

#include <QGridLayout>

#include "mainform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent)
    : MoveableFramelessWindow(parent), ui(new Ui::LoginForm) {
  ui->setupUi(this);

  //关联登录按钮点击
  connect(ui->pbLogin, SIGNAL(clicked()), this, SLOT(doLoginButClick()));
}

LoginForm::~LoginForm() { delete ui; }

QWidget *LoginForm::getDragnWidget() { return ui->login_top_widget; }

void LoginForm::doLoginButClick() {
  MainForm *m = new MainForm;
  m->show();
  this->hide();
}

void LoginForm::on_pbSignup_clicked() {
  Signup *s = new Signup();
  s->setModal(true);
  s->show();
}
