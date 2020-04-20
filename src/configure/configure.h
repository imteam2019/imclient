#ifndef CONFIGURE_H
#define CONFIGURE_H

/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Confiture module of the IM Toolkit.
** It's used to for application config info.
**
** Created by: Shengbo.Zeng
** Created date: 02/21/2020
**
**
**
****************************************************************************/

#include <QCoreApplication>
#include <QDir>
#include <QStandardPaths>
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

#include "basicconfigure.h"
#include "common/rapidjson/document.h"
#include "common/rapidjson/stringbuffer.h"
#include "common/rapidjson/writer.h"
#include "dbconfigure.h"
#include "storage/sqlitehandle.h"

using namespace std;
using rapidjson::Document;
using rapidjson::Value;
class Configure {
 public:
  inline static DBConfigure* getDBConfig() { return Configure::dbconfig; };
  inline static BasicConfigure* getBasicConfig() {
    return Configure::basicconfig;
  };

 private:
  static BasicConfigure* basicconfig;
  static DBConfigure* dbconfig;
};

#endif  // CONFIGURE_H
