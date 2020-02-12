#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>

#include "common/encrypt.h"
#include "message/data.h"
#include "network/httpconn.h"
#include "signin.h"

namespace Ui {
class Signup;
}

using namespace std;
class Signup : public QDialog {
  Q_OBJECT

 public:
  explicit Signup(QWidget *parent = nullptr);
  ~Signup();
  static void getPublicKey(QString reply, int replyFlag,
                           void *pObject);  //获取公钥回调函数
  static void registe(QString reply, int replyFlag,
                      void *pObject);  //注册回调函数
  void doGetPublicKey(QString, int);   //处理获取公钥返回数据
  void doGetRegiste(QString, int);     //处理注册返回数据

 private slots:
  void on_pbOk_clicked();
  void on_pbCancel_clicked();
  void on_teDesc_textChanged();

  void on_pbSelPic_clicked();

 private:
  Ui::Signup *ui;
  HTTPConn *hc;
  QString strPK;
  QString checkInput();
};

#endif  // SIGNUP_H
