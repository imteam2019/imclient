#include "msghandle.h"

MSGHandle::MSGHandle() { this->tc = new TCPConn(); }

void MSGHandle::init() { return; }

/**
 * @brief MSGHandle::newArrival 新消息到达回调函数
 * @param reply
 * @param replyFlag
 * @param pObject
 */
void MSGHandle::newArrivalFromNW(std::string strData, size_t flag,
                                 void *pObject) {
  // Signup *pthis = (Signup *)pObject;
  // pthis->doGetRegiste(reply, replyFlag);
}

void MSGHandle::registCallbackPFUNC_NewSendToUI(PFUNC_NewSendToUI ptrFunc,
                                                void *ptrUser) {
  this->ptrFuncNewArraivalToUI = ptrFunc;
  this->ptrNewArraivalToUI = ptrUser;
}

MSGSummary *MSGHandle::getMessageSummary(Message *m) {
  if (m == nullptr) return nullptr;
  MSGSummary *ms = m->getMessageSummary();

  //如果Message对象没有摘要，则自动为其创建，相关值为初始值
  if (ms == nullptr) {
    ms = new MSGSummary();
    Encrypt e;
    ms->session = m->msg->session;
    ms->from_user = m->msg->from_user;
    ms->msg_id = m->msg->msg_id;
    ms->to_user = m->msg->to_user;
    ms->is_group_msg = m->msg->is_group_msg;
    ms->sendCount = MSGHandle::MAX_SEND_COUNT;
    ms->msgStatus = MsgStatus::MSG_STATUS_READY;
    std::string *json = m->toJSON();
    ms->hash = e.getMD5(json, (unsigned int)json->length());
    ms->msg_length = (unsigned int)json->length();

    // 将新生成的摘要数据附在Message上
    m->msgSummary = ms;
  }
  return ms;
}
void MSGHandle::sendMessage(unsigned int is_group_msg, unsigned int from_user,
                            unsigned int to_user, std::string msg_content) {
  Message *msg = new Message(is_group_msg, from_user, to_user, msg_content);
  //对新消息生成消息摘要，然后入队列
  this->getMessageSummary(msg);
  this->sendQueue.push(*msg);

  // TODO 调用网络层回调函数做后续处理
  std::string *json = msg->toJSON();
  std::string *base64 = Encrypt::getBase64Encode(
      json->c_str(), msg->msgSummary->msg_length, false);
  cout << endl << *json << endl;
  cout << endl << *base64 << endl;
  this->tc->sendMessage(base64, base64->length());
}
std::string *toJSON(Message *m) {
  if (m == nullptr) return nullptr;
  return m->toJSON();
}
