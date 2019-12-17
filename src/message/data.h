#ifndef DATA_H
#define DATA_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Data module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 12/4/2019
**
**
**
****************************************************************************/
#include <QDebug>
#include <QVariant>
#include <QtGlobal>
#include <iostream>

#include "boost/any.hpp"
#include "boost/unordered_map.hpp"
#include "common/rapidjson/document.h"
#include "common/rapidjson/filereadstream.h"
#include "common/rapidjson/filewritestream.h"
#include "common/rapidjson/prettywriter.h"
#include "common/rapidjson/stringbuffer.h"
#include "common/rapidjson/writer.h"

using namespace std;
class Data {
 public:
  Data();
  enum enumType { JSON, XML };
  static std::string format(QMap<std::string, QVariant> *data, int formatName);
  static std::string *format(
      boost::unordered_map<std::string, boost::any> *data, int formatName);
  static void testJson();

 private:
  static std::string *formatAsJson(QMap<std::string, QVariant> *data,
                                   int formatName);
  static std::string *formatAsXml(QMap<std::string, QVariant> *data,
                                  int formatName);
};

#endif  // DATA_H
