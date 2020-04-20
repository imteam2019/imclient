#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextBlock>
#include <QTextDocument>
#include <QTextFrame>
#include <list>
#include <map>

#include "configure/basicconfigure.h"
#include "configure/configure.h"
#include "configure/dbconfigure.h"
#include "imtextedit.h"
#include "message/message.h"
#include "message/msghandle.h"
#include "network/tcpconn.h"
#include "person.h"
#include "storage/sqlitehandle.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
 signals:
  void msgWritingEmpty();

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  TCPConn *tc;
  MSGHandle *msgHandle;

  // 新到达消息回调函数
  static void newArrival(
      unsigned int is_group_msg,  //  是否是群消息, 0:非群发消息，1:群发消息
      unsigned int from_user,  //如果是群消息from_user就是发送
      unsigned int
          to_user,  // 如果是群消息就是目标群的group_id，如果不是群消息就是目标用户的user_id
      std::string msg_content,  //消息内容
      void *pObject);
 private slots:
  void on_btnSendMsg_clicked();
  void on_btnAddFriend_clicked();

 private:
  Ui::MainWindow *ui;
  QTextFrameFormat *myFormat;
  QTextFrameFormat *osFormat;
  IMTextEdit *teMessage;
  list<Person *> *lstmyfriends;

 private:
  bool setFriendsList();
  bool setMsgStyle();
  void stringToHtmlFilter(QString &str);
  void stringToHtml(QString &str, QColor crl);
  void registCallBack();
  Q_OBJECT
};
#endif  // MAINWINDOW_H
