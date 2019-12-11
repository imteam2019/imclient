#ifndef MESSAGE_H
#define MESSAGE_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Message module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/24/2019
**
**
**
****************************************************************************/
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QHostAddress>
#include <QtGlobal>

struct MSGHeader {
  qint64 msgHeaderLength;  //消息头长度
  qint64 msgBodyLength;    //消息体长度
  char senderID[1024];     //发送方ID；
  char receiverID[1024];   //接收方ID;
  qint64 sendTimeStamp;    //消息发送时间，自Epoch（1970-01-01 00:00:00
                           // UTC）起经过的时间，以秒为单位
  qint64 status;           //消息当前状态
  qint64 sendCount;        // 消息发送次数计数
  qint64 msgType;          //消息类型，在线消息：0，离线消息：1
};

struct MSGBody {
  QByteArray msgContent;
};

struct MSG {
  MSGHeader header;
  MSGBody body;
};

class Message : public QObject {
 public:
  // static const MSG_BODY_LENGTH_MAX=
  enum MsgStatus {          //定义消息生命周期的各种状态
    MSG_STATUS_READY = 0,   //新消息，已经准备好待发送
    MSG_STATUS_SENDED = 1,  //消息已经发送，接收方是否已处理未知
    MSG_STATUS_RECIVED = 2,  //消息已由接收方处理完毕
    MSG_STATUS_FAILED = 3    //消息发送失败，并已超过重发限制
  };
  Message();
  Message(const Message &m);
  ~Message();

  Message &operator=(const Message &m);
  bool operator==(const Message &m);

  qint64 getMsgSize();
  qint64 getMsgHeaderSize();
  qint64 getMsgBodySize();

  MSGHeader *getMsgHeader();
  MSGBody *getMsgBody();
  MSG *getMsg();

  void setSenderID(char *strSenderID, int len);
  void setReciverID(char *strReciverID, int len);
  void setMsgContent(QByteArray *msgContent);

  friend bool operator<(const Message &m1, const Message &m2);

  //友元声明，流插入运算符和流提取运算符函数
  friend QDataStream &operator<<(QDataStream &out, Message &m);
  friend QDataStream &operator>>(QDataStream &in, Message &m);

 private:
  MSGHeader *mh;  //消息头指针
  MSGBody *mb;    //消息体指针
  MSG *msg;       //消息指针

  void init();
  MSGHeader *msgHeaderCopy(MSGHeader &d);
};
/*
//自身声明，小于号函数必须用两个参数的全局函数
bool operator<(const Message &m1, const Message &m2);

//自身声明，流插入运算符和流提取运算符函数
QDataStream &operator<<(QDataStream &out, const Message &m);
QDataStream &operator>>(QDataStream &in, Message &m);

QDataStream &operator<<(QDataStream &out, const MSGHeader &h);
QDataStream &operator>>(QDataStream &in, MSGHeader &h);
*/
#endif  // MESSAGE_H
