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

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <algorithm>
#include <iostream>
#include <list>
#include <string>

#include "configure/configure.h"
#include "configure/dbconfigure.h"

using namespace std;
class SqliteHandle {
 public:
  enum DBStatus { closed, opend };
  SqliteHandle();
  ~SqliteHandle();
  inline bool isOpend() { return this->sqlitedbstatus == SqliteHandle::opend; }
  int exec(std::string sql, vector<std::string> *values,
           list<map<std::string, std::string> *> *results = nullptr);

 private:
  int sqlitedbstatus =
      SqliteHandle::closed;  //记录db状态，0:空闲可打开状态，1:已打开状态
                             // sqlite3 *conn = nullptr;
                             //  sqlite3_stmt *stmt = nullptr;
  DBConfigure *dbc = nullptr;
  QSqlDatabase db;
  QSqlQuery *qry;
};

#endif  // SQLITEHANDLE_H
