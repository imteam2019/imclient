#ifndef CRYPTO_H
#define CRYPTO_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Encrypt module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/24/2019
**
**
**
****************************************************************************/
#include <QString>
#include<QTime>
#include <QByteArray>
#include <QDebug>
//#include "md5.h"
#include "openssl/md5.h"

class Encrypt
{
public:
    Encrypt();
    QByteArray * encrypt(const QByteArray *);
    QString * encrypt(const QString *);
    QByteArray * decrypt(const QByteArray *);
    QString * decrypt(const QString *);
    static QString getMD5(QByteArray data);
    static QString getRandKey();

private:
    static const int KEY_RAND_LENGTH=32;//本地随机密钥长度
};

#endif // CRYPTO_H
