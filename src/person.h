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
  enum genderType { male, female, other };  //性别枚举
  enum constellationsType {
    aries,
    taurus,
    gemini,
    cancer,
    leo,
    virgo,
    libra,
    scorpio,
    sagittarius,
    capricorn,
    aquarius,
    pisces
  };  //星座枚举
  Person();
  ~Person();
  Person(const Person& person);
  Person& operator=(const Person& person);
  bool operator==(const Person& person);
  std::string getID();
  void setID(std::string id);
  std::string getNickName();
  void setNickName(std::string strNickName);
  std::string getSignature();
  void setSignature(std::string strSign);
  int getStatus();
  void setStatus(int);

 private:
  std::string* strNickName;   //昵称
  std::string* strID;         //唯一识别号
  std::string* strSignature;  //签名
  int intGender;              //性别
  int intConstellations;      //星座
  std::string* strBirthday;   //出生日期
  std::string* strMobile;     //移动电话
  std::string* strTel;        //固定电话
  std::string* strEmail;      // Email
  int intStatus;              //状态
};

#endif  // PERSON_H
