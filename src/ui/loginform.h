#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

#include "login/signup.h"
#include "moveableframelesswindow.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public MoveableFramelessWindow {
  Q_OBJECT

 public:
  explicit LoginForm(QWidget *parent = nullptr);
  ~LoginForm();

 protected:
  QWidget *getDragnWidget();
 private slots:
  /**
   * @brief 登录按钮点击
   */
  void doLoginButClick();

  void on_pbSignup_clicked();

 private:
  Ui::LoginForm *ui;
};

#endif  // LOGINFORM_H
