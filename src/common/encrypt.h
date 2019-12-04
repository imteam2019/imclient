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
#include <QByteArray>
class Encrypt
{
public:
    Encrypt();
    QByteArray * encrypt(const QByteArray *);
    QString * encrypt(const QString *);
    QByteArray * decrypt(const QByteArray *);
    QString * decrypt(const QString *);
};

#endif // CRYPTO_H
