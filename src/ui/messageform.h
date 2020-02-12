#ifndef MESSAGEFORM_H
#define MESSAGEFORM_H

#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QTextBlock>
#include <QTextDocument>
#include <QTextFrame>

#include "imtextedit.h"
#include "message/message.h"
#include "message/msghandle.h"
#include "network/tcpconn.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MessageForm;
}
QT_END_NAMESPACE

class MessageForm : public QMainWindow {
 public:
  MessageForm(QWidget *parent = nullptr);
  ~MessageForm();
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
  Ui::MessageForm *ui;
  QTextFrameFormat *myFormat;
  QTextFrameFormat *osFormat;
  bool setMsgStyle();
  void stringToHtmlFilter(QString &str);
  void stringToHtml(QString &str, QColor crl);
  IMTextEdit *teMessage;

  void registCallBack();
  Q_OBJECT
};
#endif  // MESSAGEFORM_H
