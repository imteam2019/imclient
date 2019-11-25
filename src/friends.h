#ifndef FRIEND_H
#define FRIEND_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Friends Info module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/23/2019
**
**
**
****************************************************************************/
#include "person.h"
#include <QString>
#include <QLinkedList>

class Friends
{
public:
    Friends();
    ~Friends();
    Person * getFriend();
    Person * getNext();
    bool add(Person *);//加入好友
    Person * del(Person *);//删除指定的好友
    Person * find(QString id);//按id找到指定好友
private:
    QLinkedList<Person> *plist;
    void setNext(Person *next);
    bool saveFriendtoLocal(QLinkedList<Person> *);
    bool saveFriendtoRemote(QLinkedList<Person> *);
    QLinkedList<Person> * loadFriendFromLocal();
    QLinkedList<Person> * loadFriendFromRemote();
};

#endif // FRIEND_H
