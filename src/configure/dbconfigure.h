#ifndef DBCONFIGURE_H
#define DBCONFIGURE_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Storage module of the IM Toolkit.
** It's used to for config sqlite basic info.
**
** Created by: Shengbo.Zeng
** Created date: 02/14/2020
**
**
**
****************************************************************************/
#include <QDebug>
#include <QDir>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

#include "common/rapidjson/document.h"
#include "common/rapidjson/stringbuffer.h"
#include "common/rapidjson/writer.h"

using namespace std;
using rapidjson::Document;
using rapidjson::Value;

typedef map<size_t, std::string> SqlTemp;
typedef pair<std::string, std::string> KVPair;
struct dbDetails {
  std::string ID;
  std::string TableName;
  std::string Fields;
  map<std::string, std::string> *SQL;
};
class DBConfigure {
 public:
  DBConfigure(std::string dbconfigfile);
  ~DBConfigure();
  std::string getTableName(std::string id);
  std::string getFields(std::string id);
  std::string getSQL(std::string id, std::string key);

 private:
  std::list<struct dbDetails *> *dbinfo;
  Document *dbDoc;
  std::string dbconfigfile = "";

  void init();
};

#endif  // DBCONFIGURE_H
