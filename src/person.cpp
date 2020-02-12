#include "person.h"

#include "mainwindow.h"

Person::Person() {
  this->strID = new std::string();
  this->strNickName = new std::string();
  this->strSignature = new std::string();
  this->intStatus = Person::online;
}

Person::Person(const Person &person) {
  this->setID(*person.strID);
  this->setNickName(*person.strNickName);
}

Person::~Person() {
  delete this->strID;
  delete this->strNickName;
  delete this->strSignature;
}

Person &Person::operator=(const Person &p) {
  this->setID(*p.strID);
  this->setNickName(*p.strNickName);
  return *this;
}

bool Person::operator==(const Person &p) {
  if (0 == this->strID->compare(*p.strID))
    return true;
  else
    return false;
}

/**
 * @brief Person::getID
 * @return QString
 * @desc 返回当前的id
 */
std::string Person::getID() { return *this->strID; }

/**
 * @brief Person::setID
 * @param id
 * @desc 设定指定id，如果为空则不修改
 */
void Person::setID(std::string id) {
  if (id.length() > 0) *this->strID = id;
}

/**
 * @brief Person::getNickName
 * @return QString
 * @desc 返回当前昵称
 */
std::string Person::getNickName() { return *this->strNickName; }

/**
 * @brief Person::setNickName
 * @param nickName
 * @desc 设定指定昵称，如果为空则不修改
 */
void Person::setNickName(std::string nickName) {
  if (nickName.length() > 0) *this->strNickName = nickName;
}

/**
 * @brief Person::getSign 获取签名
 * @return 返回当前签名
 */
std::string Person::getSignature() { return *this->strSignature; }

/**
 * @brief Person::setSign 根据指定字符串设定签名
 * @param strSign
 */
void Person::setSignature(std::string strSign) {
  if (strSign.length() > 0) *this->strSignature = strSign;
}

/**
 * @brief Person::getStatus 获取当前状态
 * @return
 */
int Person::getStatus() { return this->intStatus; }

/**
 * @brief Person::setStatus 设置指定状态
 * @param status
 */
void Person::setStatus(int status) {
  if (status >= Person::online && status <= Person::away)
    this->intStatus = status;
}
