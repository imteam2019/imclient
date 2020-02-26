#include "person.h"

#include "mainwindow.h"

Person::Person() {
  this->create();
  return;
}

Person::Person(const Person &person) {
  *this = person;
  return;
}

Person::Person(map<std::string, std::string> *data) {
  if (data != nullptr) {
    this->setID(data->find("ID")->second);
    this->setNickName(data->find("NickName")->second);
    this->setSignature(data->find("Signature")->second);
    this->setGender(std::stoi(data->find("Gender")->second));
    this->setConstellations(std::stoi(data->find("Constellations")->second));
    this->setBirthday(data->find("Birthday")->second);
    this->setMobile(data->find("Mobile")->second);
    this->setTel(data->find("Tel")->second);
    this->setEmail(data->find("Email")->second);
    this->setRegisterTime(std::stof(data->find("RegisterTime")->second));
    this->setCreateTime(std::stof(data->find("CreateTime")->second));
    this->setStatus(Person::unknown);
  } else
    this->create();
}

Person::~Person() {
  delete this->ID;
  delete this->NickName;
  delete this->Signature;
  delete this->Tel;
  delete this->Email;
  delete this->Birthday;
  delete this->Mobile;
}

void Person::create() {
  this->setID("");
  this->setNickName("");
  this->setSignature("");
  this->setGender(Person::other);
  this->setConstellations(Person::aries);
  this->setBirthday("");
  this->setMobile("");
  this->setTel("");
  this->setEmail("");
  this->setRegisterTime(0);
  this->setCreateTime(0);
  this->setStatus(Person::unknown);
}

Person &Person::operator=(const Person &person) {
  this->setID(*person.ID);
  this->setNickName(*person.NickName);
  this->setSignature(*person.Signature);
  this->setGender(person.Gender);
  this->setConstellations(Person::aries);
  this->setBirthday(*person.Birthday);
  this->setMobile(person.getMobile());
  this->setTel(person.getTel());
  this->setEmail(person.getEmail());
  this->setRegisterTime(person.getRegisterTime());
  this->setCreateTime(person.getCreateTime());
  this->setStatus(person.intStatus);
  return *this;
}

bool Person::operator==(const Person &p) {
  if (0 == this->ID->compare(*p.ID))
    return true;
  else
    return false;
}

/**
 * @brief Person::getID
 * @return QString
 * @desc 返回当前的id
 */
std::string Person::getID() { return *this->ID; }

/**
 * @brief Person::setID
 * @param id
 * @desc 设定指定id，如果为空则不修改
 */
void Person::setID(std::string value) {
  this->ID = new std::string(value);
  return;
}

/**
 * @brief Person::getNickName
 * @return QString
 * @desc 返回当前昵称
 */
std::string Person::getNickName() { return *this->NickName; }

/**
 * @brief Person::setNickName
 * @param nickName
 * @desc 设定指定昵称，如果为空则不修改
 */
void Person::setNickName(std::string value) {
  this->NickName = new std::string(value);
  return;
}

/**
 * @brief Person::getSign 获取签名
 * @return 返回当前签名
 */
std::string Person::getSignature() { return *this->Signature; }

/**
 * @brief Person::setSign 根据指定字符串设定签名
 * @param strSign
 */
void Person::setSignature(std::string value) {
  this->Signature = new std::string(value);
  return;
}

int Person::getStatus() { return this->intStatus; }
/**
 * @brief Person::setStatus 设置指定状态
 * @param status
 */
void Person::setStatus(int status) {
  if (status >= Person::online && status <= Person::away)
    this->intStatus = status;
}

int Person::getGender() { return this->Gender; }
void Person::setGender(int gender) {
  if (gender != Person::male && gender != Person::female &&
      gender != Person::other)
    return;
  this->Gender = gender;
}

int Person::getConstellations() { return this->Constellations; }
void Person::setConstellations(int cs) {
  if (cs < Person::aries || cs > Person::pisces) return;
  this->Constellations = cs;
}

const std::string Person::getBirthday() { return *this->Birthday; }
void Person::setBirthday(std::string birthday) {
  // todo 需要进行日期字符串有效性验证
  if (birthday.length() <= 0) return;
  this->Birthday = new std::string(birthday);
}
const std::string Person::getMobile() const { return *this->Mobile; }

void Person::setMobile(std::string value) {
  this->Mobile = new std::string(value);
  return;
}

const std::string Person::getTel() const { return *Tel; }

void Person::setTel(std::string value) {
  this->Tel = new std::string(value);
  return;
}

const std::string Person::getEmail() const { return *Email; }

void Person::setEmail(std::string value) {
  this->Email = new std::string(value);
  return;
}

float Person::getRegisterTime() const { return RegisterTime; }

void Person::setRegisterTime(float value) {
  // todo 增加时间判断处理
  RegisterTime = value;
}

float Person::getCreateTime() const { return CreateTime; }

void Person::setCreateTime(float value) {
  // todo 增加时间判断处理
  CreateTime = value;
}
