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
#include <QDebug>
#include <QtGlobal>

struct MSGHeader {
  size_t msgHeaderLength;  //消息头长度
  size_t msgBodyLength;    //消息体长度
  char senderID[1024];     //发送方ID；
  char receiverID[1024];   //接收方ID;
  time_t sendTimes;        //消息发送时间，自Epoch（1970-01-01 00:00:00
                           // UTC）起经过的时间，以秒为单位
  size_t status;           //消息当前状态
  size_t sendCount;        // 消息发送次数计数
  size_t msgType;          //消息类型，在线消息：0，离线消息：1
};

struct MSGBody {
  QByteArray msgContent;
};

struct MSG {
  MSGHeader header;
  MSGBody body;
};

class Message {
 public:
  // static const MSG_BODY_LENGTH_MAX=
  enum MsgStatus {          //定义消息生命周期的各种状态
    MSG_STATUS_READY = 0,   //新消息，已经准备好待发送
    MSG_STATUS_SENDED = 1,  //消息已经发送，接收方是否已处理未知
    MSG_STATUS_RECIVED = 2,  //消息已由接收方处理完毕
    MSG_STATUS_FAILED = 3    //消息发送失败，并已超过重发限制
  };
  Message();
  ~Message();

  size_t getMsgSize();
  size_t getMsgHeaderSize();
  size_t getMsgBodySize();

  const MSGHeader *getMsgHeader();
  const MSGBody *getMsgBody();
  const MSG *getMsg();

  void setSenderID(char *strSenderID, int len);
  void setReciverID(char *strReciverID, int len);
  void setMsgContent(QByteArray *msgContent);

 private:
  MSGHeader *mh;  //消息头指针
  MSGBody *mb;    //消息体指针
  MSG *msg;       //消息指针
};

#endif  // MESSAGE_H
