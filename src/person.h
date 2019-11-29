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
#include <QtGlobal>
class Person
{
public:
    enum enumType{online,offline,invisible,away};
    Person();
    ~Person();
    Person(const Person& person);
    Person & operator =(const Person& person);
    bool operator ==(const Person& person);
    QString getID();
    void setID(QString id);
    QString getNickName();
    void setNickName(QString strNickName);
    QString getSign();
    void setSign(QString strSign);
    int getStatus();
    void setStatus(int);
private:
    QString *strNickName;//昵称
    QString *strID;//唯一识别号
    QString *strSign;//签名
    int intStatus;//状态
};

#endif // PERSON_H
