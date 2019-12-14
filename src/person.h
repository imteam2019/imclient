#ifndef PERSON_H
#define PERSON_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Personal Info module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/23/2019
**
**
**
****************************************************************************/
#include <string>
class Person {
 public:
  enum enumType { online, offline, invisible, away };
  Person();
  ~Person();
  Person(const Person& person);
  Person& operator=(const Person& person);
  bool operator==(const Person& person);
  std::string getID();
  void setID(std::string id);
  std::string getNickName();
  void setNickName(std::string strNickName);
  std::string getSign();
  void setSign(std::string strSign);
  int getStatus();
  void setStatus(int);

 private:
  std::string* strNickName;  //昵称
  std::string* strID;        //唯一识别号
  std::string* strSign;      //签名
  int intStatus;             //状态
};

#endif  // PERSON_H
