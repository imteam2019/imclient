#ifndef SETTINGSHANDLE_H
#define SETTINGSHANDLE_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Settings Handle module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/27/2019
**
**
**
****************************************************************************/
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QtGlobal>
#include <iostream>

using namespace std;
class SettingsHandle {
 public:
  enum enumType { JSON, XML };
  SettingsHandle();
  virtual ~SettingsHandle();
  virtual QVariantMap *loadSettings(const QString *fileName,
                                    int filetype = SettingsHandle::JSON,
                                    bool isEncrypt = false);

 private:
  QVariantMap *loadJson(QString *);
  QVariantMap *loadXml(QString *);
};

#endif  // SETTINGSHANDLE_H
