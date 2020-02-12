#ifndef SIGNIN_H
#define SIGNIN_H

#include <QDialog>

#include "common/encrypt.h"
#include "message/data.h"

namespace Ui {
class Signin;
}

class Signin : public QDialog {
  Q_OBJECT

 public:
  explicit Signin(QWidget *parent = nullptr);
  ~Signin();

 private slots:
  void on_pbCancel_clicked();

  void on_pbOk_clicked();

  void on_pbSignup_clicked();

 private:
  Ui::Signin *ui;

  bool login(QString strLoginInfo);
};

#endif  // SIGNIN_H
