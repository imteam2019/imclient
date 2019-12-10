#include "message.h"

Message::Message() {
  this->msg = new MSG();
  this->mh = &this->msg->header;
  this->mb = &this->msg->body;
  memset(this->mh->senderID, '\0', 1024);
  memset(this->mh->receiverID, '\0', 1024);
  this->mh->msgHeaderLength = sizeof(*this->mh);
}

Message::~Message() {
  if (this->msg) {
    this->mb->msgContent.clear();
    delete this->msg;
  }
}

size_t Message::getMsgHeaderSize() { return sizeof(*this->mh); }

size_t Message::getMsgBodySize() { return (size_t)this->mb->msgContent.size(); }

size_t Message::getMsgSize() { return sizeof(*this->msg); }

const MSGHeader* Message::getMsgHeader() { return this->mh; }

const MSGBody* Message::getMsgBody() { return this->mb; }

const MSG* Message::getMsg() { return this->msg; }

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
  }
}
