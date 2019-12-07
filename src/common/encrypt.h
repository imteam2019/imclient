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
#include <QByteArray>
#include <QDebug>
#include <QString>
#include <QTime>

#include "openssl/aes.h"
#include "openssl/bio.h"
#include "openssl/des.h"
#include "openssl/md5.h"
#include "openssl/rsa.h"
#include "openssl/ssl.h"

class Encrypt {
 public:
  Encrypt();
  QByteArray *encrypt(const QByteArray *);
  QString *encrypt(const QString *);
  QByteArray *decrypt(const QByteArray *);
  QString *decrypt(const QString *);
  static QString getMD5(QByteArray data);
  // static QString getBase64(QByteArray data);
  static QString getRandKey();
  static QByteArray *getRSAEncrypt(QByteArray data, QString strPublicKey);
  static QByteArray *getRSADecrypt(QByteArray data, QString strPrivateKey);
  static QByteArray *getAESEncrypt(QByteArray data, QString strKey,
                                   int intMode);
  static QByteArray *getAESDecrypt(QByteArray data, QString strKey,
                                   int intMode);

 private:
  static const int KEY_RAND_LENGTH = 32;  //本地随机密钥长度
};

#endif  // CRYPTO_H
