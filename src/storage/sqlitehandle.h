#ifndef SQLITEHANDLE_H
#define SQLITEHANDLE_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the SqliteHandle module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 01/16/2020
**
**
**
****************************************************************************/
#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <list>
#include <string>
using namespace std;
class SqliteHandle {
 public:
  enum DBStatus { closed, opend };
  enum DataType { person, message };
  SqliteHandle(std::string* dbName);
  inline bool isOpend() { return this->sqlitedbstatus == SqliteHandle::opend; }
  int read(list<void*>* dataList, int flag);
  // int save(list<void*>* datalist, int flag);

 private:
  int sqlitedbstatus =
      SqliteHandle::closed;  //记录db状态，0:空闲可打开状态，1:已打开状态
  sqlite3* conn = nullptr;
  sqlite3_stmt* stmt = nullptr;
};

#endif  // SQLITEHANDLE_H
