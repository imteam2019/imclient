#ifndef MSGHANDLE_H
#define MSGHANDLE_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Message Handle module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 12/12/2019
**
**
**
****************************************************************************/
#include <QDebug>
#include <QFile>
#include <QObject>
#include <queue>

#include "common/encrypt.h"
#include "data.h"
#include "message/message.h"
#include "network/tcpconn.h"

/**
 * 给MSGHandle调用的新到达消息给到展现层的回调函数
 */
typedef void (*PFUNC_NewSendToUI)(
    unsigned int is_group_msg,  //  是否是群消息, 0:非群发消息，1:群发消息
    unsigned int from_user,  //如果是群消息from_user就是发送
    unsigned int
        to_user,  // 如果是群消息就是目标群的group_id，如果不是群消息就是目标用户的user_id
    std::string msg_content,  //消息内容
    void* pObject);

typedef void (*PFUNC_NewSendToNW)(std::string* data, unsigned int len,
                                  void* pObject);

class MSGHandle {
 public:
  enum MsgStatus {          //定义消息生命周期的各种状态
    MSG_STATUS_READY = 0,   //新消息，已经准备好待发送
    MSG_STATUS_SENDED = 1,  //消息已经发送，接收方是否已处理未知
    MSG_STATUS_RECIVED = 2,  //消息已由接收方处理完毕
    MSG_STATUS_FAILED = 3    //消息发送失败，并已超过重发限制
  };

  const static int MAX_SEND_COUNT = 3;
  MSGHandle();
  void init();
  ~MSGHandle();

  std::string* toJSON(Message* m);
  //网络层新数据到达回调函数
  static void newArrivalFromNW(std::string strData, size_t flag, void* pObject);

  // 定义消息分隔符
  const std::string& Delimiter() {
    // Initialize the static variable
    static std::string strDelimiter("\r\n\r\n");
    return strDelimiter;
  }

  void registCallbackPFUNC_NewSendToUI(PFUNC_NewSendToUI ptrFunc,
                                       void* ptrUser);

  std::queue<Message> sendQueue;     //待发送消息队列
  std::queue<Message> receiveQueue;  //已收到未处理的消息队列

  MSGSummary* getMessageSummary(Message* m);
  void sendMessage(unsigned int is_group_msg, unsigned int from_user,
                   unsigned int to_user, std::string msg_content);

 private:
  PFUNC_NewSendToUI ptrFuncNewArraivalToUI;
  void* ptrNewArraivalToUI;

  PFUNC_NewSendToNW ptrFuncNewSendToNW;
  void* ptrNewSendToNW;

  TCPConn* tc;

  // Q_OBJECT
};

#endif  // MSGHANDLE_H
