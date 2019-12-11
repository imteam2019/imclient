#include "message.h"

Message::Message() { init(); }

Message::Message(const Message& m) {
  init();
  this->msgHeaderCopy(*(m.mh));
  this->mb->msgContent.clear();
  this->mb->msgContent.append(m.mb->msgContent);
}

Message::~Message() {
  if (this->msg) {
    this->mb->msgContent.clear();
    delete this->msg;
  }
}

void Message::init() {
  this->msg = new MSG();
  this->mh = &this->msg->header;
  this->mb = &this->msg->body;
  memset(this->mh->senderID, '\0', 1024);
  memset(this->mh->receiverID, '\0', 1024);
  this->mh->msgHeaderLength = sizeof(*this->mh);
  this->mh->sendTimeStamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
}

/**
 * @brief Message::operator = 重载赋值运算符
 * @param m
 * @return
 */
Message& Message::operator=(const Message& m) {
  Message* message = new Message(m);
  return *message;
}

/**
 * @brief Message::operator == 重载比较运算符
 * @param m
 * @return
 */
bool Message::operator==(const Message& m) {
  return (this->mb->msgContent.length() == m.mb->msgContent.length() &&
          !memcmp(this->mh, m.mh, sizeof(MSGHeader)) &&
          !memcmp(this->mb->msgContent.data(), m.mb->msgContent.data(),
                  (size_t)m.mb->msgContent.length()));
}

/**
 * @brief operator < 重载运算符，用于比较两个消息的发送时间哪个更早，用于排序
 * @param m1
 * @param m2
 * @return 如果m1的发送时间早于m2的发送时间，则为true，否则false
 */

bool operator<(const Message& m1, const Message& m2) {
  return m1.mh->sendTimeStamp < m2.mh->sendTimeStamp;
}

/**
 * @brief operator << Message类重载<<运算符，输出消息头和消息体
 * @param out QDataStream
 * @param m Message类实例
 * @return QDataStream
 */
QDataStream& operator<<(QDataStream& out, Message& m) {
  // QByteArray b;
  // memcpy(b.data(), (const char*)m.getMsgHeader(), sizeof(MSGHeader));
  int i = out.writeRawData((const char*)m.getMsgHeader(), sizeof(MSGHeader));
  out.writeRawData(m.getMsgBody()->msgContent.data(),
                   m.getMsgBody()->msgContent.size());
  /*
    out << h->msgHeaderLength << h->msgBodyLength << h->senderID <<
    h->receiverID
        << h->sendTimes << h->status << h->sendCount << h->msgType
        << m.getMsgBody()->msgContent;
  */
  return out;
}

QDataStream& operator>>(QDataStream& in, Message& m) {
  QByteArray bufTmp;
  MSGHeader* hTmp = m.getMsgHeader();
  in >> bufTmp;
  memcpy((void*)hTmp, bufTmp.data(), sizeof(MSGHeader));
  m.getMsgBody()->msgContent.append(bufTmp);
  return in;
}

MSGHeader* Message::msgHeaderCopy(MSGHeader& d) {
  memcpy(this->mh, &d, sizeof(MSGHeader));
  return this->mh;
}
qint64 Message::getMsgHeaderSize() { return sizeof(*this->mh); }

qint64 Message::getMsgBodySize() { return this->mb->msgContent.size(); }

qint64 Message::getMsgSize() {
  return this->getMsgHeaderSize() + this->getMsgBodySize();
}

MSGHeader* Message::getMsgHeader() { return this->mh; }

MSGBody* Message::getMsgBody() { return this->mb; }

MSG* Message::getMsg() { return this->msg; }

void Message::setSenderID(char* strSenderID, int len) {
  if (strSenderID && len > 0 && len < 1024) {
    memcpy(this->mh->senderID, strSenderID, len);
    this->mh->senderID[len] = '\0';
  }
}
void Message::setReciverID(char* strReciverID, int len) {
  if (strReciverID && len > 0 && len < 1024) {
    memcpy(this->mh->receiverID, strReciverID, len);
    this->mh->senderID[len] = '\0';
  }
}

void Message::setMsgContent(QByteArray* msgContent) {
  if (msgContent) {
    this->mb->msgContent.clear();
    this->mb->msgContent.append(*msgContent);
    this->mh->msgBodyLength = msgContent->size();
  }
}
