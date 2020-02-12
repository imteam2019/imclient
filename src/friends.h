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

#include <iostream>
#include <map>
#include <string>

#include "person.h"

typedef std::map<std::string, Person> MAPFRIENDS;
class Friends {
 public:
  Friends();
  ~Friends();
  Person *getFriend();
  Person *getNext();
  bool add(Person *);            //加入好友
  Person *del(Person *);         //删除指定的好友
  Person *find(std::string id);  //按id找到指定好友
 private:
  MAPFRIENDS *fmap;
  void setNext(Person *next);
  bool saveFriendtoLocal(MAPFRIENDS *);
  bool saveFriendtoRemote(MAPFRIENDS *);
  MAPFRIENDS *loadFriendFromLocal();
  MAPFRIENDS *loadFriendFromRemote();
};

#endif  // FRIEND_H
