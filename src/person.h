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
    Person();
    ~Person();
    Person(const Person& person);
    Person & operator =(const Person& person);
    bool operator ==(const Person& person);
    QString getID();
    QString getNickName();
    void setID(QString id);
    void setNickName(QString strNickName);
private:
    QString *strNickName;//昵称
    QString *strID;//唯一识别号
};

#endif // PERSON_H
