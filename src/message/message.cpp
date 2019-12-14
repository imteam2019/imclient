#include "message.h"

Message::Message() { init(); }

Message::Message(const Message& m) {
  init();
  msg->session.append(m.msg->session);
  msg->is_group_msg = m.msg->is_group_msg;
  msg->from_user = m.msg->from_user;
  msg->to_user = m.msg->to_user;
  msg->msg_id = m.msg->msg_id;
  msg->msg_type.append(m.msg->msg_type);
  msg->msg_content.append(m.msg->msg_content);
  msg->msg_time = m.msg->msg_time;
  msg->device.append(m.msg->device);
  msg->target_device.append(m.msg->target_device);
  msg->target_user = m.msg->target_user;
  msg->global_id = m.msg->global_id;
  msg->version.append(m.msg->version);
  msg->group_id = m.msg->group_id;
  msg->gate_no.append(m.msg->gate_no);
  msg->is_disturb = m.msg->is_disturb;
}

/**
 * @brief Message::Message
 * @param is_group_msg 是否是群消息, 0:非群发消息，1:群发消息
 * @param from_user 如果是群消息from_user就是发送
 * @param to_user
 * 如果是群消息就是目标群的group_id，如果不是群消息就是目标用户的user_id
 * @param msg_content 消息内容
 */
Message::Message(unsigned int is_group_msg, unsigned int from_user,
                 unsigned int to_user, std::string msg_content) {
  init();
  msg->is_group_msg = is_group_msg;
  msg->from_user = from_user;
  msg->to_user = to_user;
  msg->msg_content.append(msg_content);
  return;
}
Message::~Message() {
  if (this->msg) {
    delete this->msg;
  }
  if (this->msgSummary) {
    delete this->msgSummary;
  }
}

void Message::init() {
  this->msg = new M();
  this->msgSummary = nullptr;
  this->msg->msg_time =
      std::chrono::system_clock::now().time_since_epoch().count();
}

/**
 * @brief Message::operator = 重载赋值运算符
 * @param m
 * @return
 */
Message& Message::operator=(const Message& m) {
  Message* mes = new Message(m);
  return *mes;
}

/**
 * @brief Message::operator == 重载比较运算符
 * 如果两个消息的session和msg id都一致，则两个为同一消息
 * @param m
 * @return
 */
bool Message::operator==(const Message& m) {
  return (!this->msg->session.compare(m.msg->session) &&
          this->msg->msg_id == m.msg->msg_id);
}

/**
 * @brief operator << Message类重载<<运算符，输出消息
 * @param out std::ostream &
 * @param m Message类实例
 * @return std::ostream &
 */
std::ostream& operator<<(std::ostream& out, Message& m) {
  M* msg = m.msg;
  if (msg == nullptr) return out << "Nothing";
  out << msg->session << msg->is_group_msg << msg->from_user << msg->to_user
      << msg->msg_id << msg->msg_type << msg->msg_content << msg->msg_time
      << msg->device << msg->target_device << msg->target_user << msg->global_id
      << msg->version << msg->group_id << msg->gate_no << msg->is_disturb;

  return out;
}

std::istream& operator>>(std::istream& in, Message& m) {
  M* msg = m.msg;
  if (msg == nullptr) return in;
  in >> msg->session >> msg->is_group_msg >> msg->from_user >> msg->to_user >>
      msg->msg_id >> msg->msg_type >> msg->msg_content >> msg->msg_time >>
      msg->device >> msg->target_device >> msg->target_user >> msg->global_id >>
      msg->version >> msg->group_id >> msg->gate_no >> msg->is_disturb;

  return in;
}

MSGSummary* Message::getMessageSummary() {
  //
  return this->msgSummary;
}

void Message::setMessageSummary(MSGSummary* ptrSummary) {
  if (ptrSummary != nullptr) {
    this->msgSummary = ptrSummary;
  }
}

unsigned long Message::getMsgBodySize() {
  return this->msg->msg_content.size();
}

unsigned long Message::getMsgSize() {
  unsigned long msgsize = 0;
  msgsize +=
      msg->session.size() + sizeof(msg->is_group_msg) + sizeof(msg->from_user) +
      sizeof(msg->to_user) + sizeof(msg->msg_id) + msg->msg_type.size() +
      msg->msg_content.size() + sizeof(msg->msg_time) + msg->device.size() +
      msg->target_device.size() + sizeof(msg->target_user) +
      sizeof(msg->global_id) + msg->version.size() + sizeof(msg->group_id) +
      msg->gate_no.size() + sizeof(msg->is_disturb);
  return msgsize;
}

/**
 * @brief Message::toJSON  将消息转换成json格式
 * @return std::string* 失败则返回nullper
 */
std::string* Message::toJSON() {
  if (msg == nullptr) return nullptr;
  std::string* strJSON = new std::string();
  M* msg = this->msg;
  strJSON->append("{");

  strJSON->append("\"session\":\"" + msg->session + "\",");
  strJSON->append("\"is_group_msg\":\"" + std::to_string(msg->is_group_msg) +
                  "\",");
  strJSON->append("\"from_user\":\"" + std::to_string(msg->from_user) + "\",");
  strJSON->append("\"to_user\":\"" + std::to_string(msg->to_user) + "\",");
  strJSON->append("\"msg_id\":\"" + std::to_string(msg->msg_id) + "\",");
  strJSON->append("\"msg_type\":\"" + msg->msg_type + "\",");
  strJSON->append("\"msg_content\":\"" + msg->msg_content + "\",");
  strJSON->append("\"msg_time\":\"" + std::to_string(msg->msg_time) + "\",");
  strJSON->append("\"device\":\"" + msg->device + "\",");
  strJSON->append("\"target_device\":\"" + msg->target_device + "\",");
  strJSON->append("\"target_user\":\"" + std::to_string(msg->target_user) +
                  "\",");
  strJSON->append("\"global_id\":\"" + std::to_string(msg->global_id) + "\",");
  strJSON->append("\"version\":\"" + msg->version + "\",");
  strJSON->append("\"group_id\":\"" + std::to_string(msg->group_id) + "\",");
  strJSON->append("\"gate_no\":\"" + msg->gate_no + "\",");
  strJSON->append("\"is_disturb\":\"" + std::to_string(msg->is_disturb) + "\"");

  strJSON->append("}");
  return strJSON;
}
