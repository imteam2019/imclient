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
#include <QtGlobal>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>

class SettingsHandle
{
public:
    enum enumType{JSON,XML};
    SettingsHandle();
    ~SettingsHandle();
    QVariantMap * loadSettings(const QString *fileName,int filetype=SettingsHandle::JSON,bool isEncrypt=false);

private:
    QVariantMap * loadJson(QString *);
    QVariantMap * loadXml(QString *);
};

#endif // SETTINGSHANDLE_H
