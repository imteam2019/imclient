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
#include <message.h>

#include <QAbstractSocket>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QQueue>
#include <QTcpSocket>

class TCPConn : public QObject {
 public:
  TCPConn();
  ~TCPConn();

  void sendMessage(Message &m);
  void sendMessage(const char *, int);
 signals:
  void queueEmpty(QQueue<Message> &e);
  void finishRead(char *data, size_t len);

 private slots:
  void doConnected();
  void doDisconnected();
  void bytesWritten(qint64 len);
  void doReadyRead();
  void doFinishRead(Message &m);
  void doReadySend();
  void doFinishSend();
  void doError(QAbstractSocket::SocketError socketErr);
  void doQueueEmpty(QQueue<Message> &e);

 private:
  Q_OBJECT
  QTcpSocket *ts;
  QQueue<Message> msgSendQueue;     //消息发送队列
  QQueue<Message> msgReceiveQueue;  //消息接收队列

  qint64 savaQueueToFile();
  qint64 loadQueueFromFile();
};

#endif  // TCPCONN_H
