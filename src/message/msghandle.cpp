#include "msghandle.h"

MSGHandle::MSGHandle() {
  this->init();
  return;
}

void MSGHandle::init() {
  // this->tc = new TCPConn();

  return;
}

MSGHandle::~MSGHandle() {}
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
    // std::string *json = m->toJSON();
    std::string *json = this->toJSON(m);
    ms->hash = e.getMD5(json, (unsigned int)json->length());
    ms->msg_length = (unsigned int)json->length();

    // 将新生成的摘要数据附在Message上
    m->msgSummary = ms;
  }
  return ms;
}

/**
 * @brief MSGHandle::sendMessage
 * @param is_group_msg
 * @param from_user
 * @param to_user
 * @param msg_content
 */
void MSGHandle::sendMessage(unsigned int is_group_msg, unsigned int from_user,
                            unsigned int to_user, std::string msg_content) {
  Message *msg = new Message(is_group_msg, from_user, to_user, msg_content);
  //对新消息生成消息摘要，然后入队列
  this->getMessageSummary(msg);
  this->sendQueue.push(*msg);

  // TODO 调用网络层回调函数做后续处理
  std::string *json = this->toJSON(msg);
  std::string *base64 = Encrypt::getBase64Encode(
      json->c_str(), msg->msgSummary->msg_length, false);
  // cout << endl << *json << endl;
  // cout << endl << *base64 << endl;

  // 测试压缩
  printf("the content before compressing size is:\t%i\n", base64->size());
  std::string *com = Data::compressText(base64, base64->size());
  // cout << endl << *com << endl;

  // this->tc->sendMessage(base64, base64->length());
}

std::string *MSGHandle::toJSON(Message *m) {
  M *msg = m->getMessage();
  rapidjson::Document jsonDoc;         // JSON Document 指针
  rapidjson::StringBuffer jsonBuffer;  // JSON string buffer 指针
  rapidjson::Writer<StringBuffer> jsonWriter(jsonBuffer);  // JSON Writer
  jsonDoc.SetObject();
  rapidjson::Document::AllocatorType &allocator = jsonDoc.GetAllocator();
  jsonDoc.AddMember("session", msg->session, allocator);
  jsonDoc.AddMember("is_group_msg", msg->is_group_msg, allocator);
  jsonDoc.AddMember("from_user", msg->from_user, allocator);
  jsonDoc.AddMember("to_user", msg->to_user, allocator);
  jsonDoc.AddMember("msg_id", msg->msg_id, allocator);
  jsonDoc.AddMember("msg_type", msg->msg_type, allocator);
  jsonDoc.AddMember("msg_content", msg->msg_content, allocator);
  jsonDoc.AddMember("msg_time", msg->msg_time, allocator);
  jsonDoc.AddMember("device", msg->device, allocator);
  jsonDoc.AddMember("target_device", msg->target_device, allocator);
  jsonDoc.AddMember("target_user", msg->target_user, allocator);
  jsonDoc.AddMember("global_id", msg->global_id, allocator);
  jsonDoc.AddMember("version", msg->version, allocator);
  jsonDoc.AddMember("group_id", msg->group_id, allocator);
  jsonDoc.AddMember("gate_no", msg->gate_no, allocator);
  jsonDoc.AddMember("is_disturb", msg->is_disturb, allocator);

  jsonDoc.Accept(jsonWriter);
  std::string *b = new std::string(jsonBuffer.GetString());

#ifdef MY_DEBUG_ON
  // std::cout << jsonBuffer.GetString() << endl;
#endif

  return b;
}
