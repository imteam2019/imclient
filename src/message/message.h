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
#include <QObject>
#include <chrono>
#include <iostream>
#include <map>
#include <ostream>

using namespace std;

struct M {
  std::string session = "00000000000000000000000000000000";
  unsigned int is_group_msg = 0;  //  是否是群消息, 0:非群发消息，1:群发消息
  unsigned int from_user = 0;  //  如果是群消息from_user就是发送
  unsigned int to_user =
      0;  // 如果是群消息就是目标群的group_id，如果不是群消息就是目标用户的user_id
  unsigned int msg_id = 0;
  std::string msg_type = "";
  std::string msg_content = "";
  long long msg_time = 0;
  std::string device = "";
  std::string target_device = "mobile";
  unsigned int target_user = 0;
  unsigned int global_id = 0;   //消息的全局ID
  std::string version = "";     //消息版本号
  unsigned int group_id = 0;    //群id
  std::string gate_no = "";     // 消息节点名字
  unsigned int is_disturb = 1;  //本次消息是否推送 0推动， 1不推送
};

// 消息摘要，用于保存对应消息的处理、状态等信息
struct MSGSummary {
  std::string session = "00000000000000000000000000000000";
  unsigned int is_group_msg = 0;  //  是否是群消息, 0:非群发消息，1:群发消息
  unsigned int from_user = 0;  //  如果是群消息from_user就是发送
  unsigned int to_user =
      0;  // 如果是群消息就是目标群的group_id，如果不是群消息就是目标用户的user_id
  unsigned int msg_id = 0;
  unsigned int msg_length =
      0;  //消息最终长度，如果有编码或加密，则为编码或加密后的长度
  std::string hash;  //消息的哈希值
  unsigned int sendCount =
      3;  //消息最大发送次数，每发送一次减1，当该值为0则丢弃
  unsigned int msgStatus;  //消息实时状态，由Message enum MsgStatus 定义
};

class Message : public QObject {
 public:
  Message();
  Message(const Message &m);
  Message(unsigned int is_group_msg, unsigned int from_user,
          unsigned int to_user, std::string msg_content);
  ~Message();

  Message &operator=(const Message &m);
  bool operator==(const Message &m);

  unsigned long getMsgSize();
  unsigned long getMsgBodySize();

  std::string *toJSON();
  MSGSummary *getMessageSummary();
  void setMessageSummary(MSGSummary *ptrSummary);

  //友元声明，流插入运算符和流提取运算符函数
  friend std::ostream &operator<<(std::ostream &out, Message &m);
  friend std::istream &operator>>(std::istream &in, Message &m);

 private:
  friend class MSGHandle;
  M *msg;                  //消息指针
  MSGSummary *msgSummary;  //消息摘要指针

  void init();
};

#endif  // MESSAGE_H
