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
#include <common/common.h>

#include <list>
#include <map>
#include <string>
#include <vector>
using namespace std;
typedef map<std::string, std::string> KV;
static const std::string tablename = "t_person";
static const std::string tableFields =
    "ID,NickName,Signature,Gender,Constellations,Birthday,Mobile,Tel,Email,"
    "RegisterTime,CreateTime";

class Person {
 public:
  enum enumType { online, offline, invisible, away, unknown };
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
  Person(const Person& person);
  Person(map<std::string, std::string>* data);
  ~Person();

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

  int getGender();
  void setGender(int);

  int getConstellations();
  void setConstellations(int);

  const std::string getBirthday() const;
  void setBirthday(std::string);

  const std::string getMobile() const;
  void setMobile(std::string value);

  const std::string getTel() const;
  void setTel(std::string value);

  const std::string getEmail() const;
  void setEmail(std::string value);

  float getRegisterTime() const;
  void setRegisterTime(float value);

  float getCreateTime() const;
  void setCreateTime(float value);

 private:
  std::string* NickName;   //昵称
  std::string* ID;         //唯一识别号
  std::string* Signature;  //签名
  int Gender;              //性别
  int Constellations;      //星座
  std::string* Birthday;   //出生日期
  std::string* Mobile;     //移动电话
  std::string* Tel;        //固定电话
  std::string* Email;      // Email
  float RegisterTime;      //注册时间
  float CreateTime;        //记录创建时间
  int intStatus;           //状态

  void create();
};

#endif  // PERSON_H
