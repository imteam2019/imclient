#ifndef TCPCONN_H
#define TCPCONN_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Network Connection module of the IM Toolkit.
** It support TCP.
**
** Created by: Shengbo.Zeng
** Created date: 12/11/2019
**
**
**
****************************************************************************/
#include <message/message.h>

#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QQueue>
#include <QTcpSocket>

//#include "common/imqueue.h"

typedef void (*PNEWMESSAGE)(std::string strData, size_t flag, void *pObject);

class TCPConn : public QObject {
 public:
  static const long long RESEND_TIMES = 3;  //定义默认的消息重发次数。
  TCPConn();
  ~TCPConn();

  long long sendMessage(Message &m);
  void sendMessage(std::string *, unsigned int);

  void registCallback(PNEWMESSAGE, void *);

 signals:
  void queueEmpty(QQueue<Message> &e);
  void prepareSendArrival();  //有新的待发送消息到达
  void finishRead(char *data, size_t len);

 private slots:
  void doConnected();
  void doDisconnected();
  void bytesWritten(long long len);
  void doReadyRead();
  void doFinishRead(Message &m);
  void doReadySend();
  void doFinishSend();
  void doError(QAbstractSocket::SocketError socketErr);
  void doQueueEmpty(QQueue<Message> &e);
  void doSend();

 private:
  QTcpSocket *ts;
  QQueue<Message> *msgSendQueue;     //消息发送队列
  QQueue<Message> *msgReceiveQueue;  //消息接收队列

  PNEWMESSAGE ptrNewMassage;  //新到达数据
  void *ptrNewMsgHandle;      //处理新到达数据的对象指针

  long long savaQueueToFile();
  long long loadQueueFromFile();

  Q_OBJECT
};

#endif  // TCPCONN_H
