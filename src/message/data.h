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

#include "common/rapidjson/document.h"
#include "common/rapidjson/filereadstream.h"
#include "common/rapidjson/filewritestream.h"
#include "common/rapidjson/prettywriter.h"
#include "common/rapidjson/stringbuffer.h"

using namespace std;
class Data {
 public:
  Data();
  enum enumType { JSON, XML };
  static QString format(QMap<QString, QVariant> *data, int formatName);
  static void testJson();

 private:
  static QString formatAsJson(QMap<QString, QVariant> *data, int formatName);
  static QString formatAsXml(QMap<QString, QVariant> *data, int formatName);
};

#endif  // DATA_H
