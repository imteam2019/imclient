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
#include "openssl/err.h"
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
  QString getMD5(QByteArray data);
  // static QString getBase64(QByteArray data);
  QString getRandKey();
  QByteArray *getRSAEncrypt(QByteArray data);
  QByteArray *getRSAEncrypt(QByteArray data, QString strPublicKey);
  QByteArray *getRSADecrypt(QByteArray data);
  QByteArray *getRSADecrypt(QByteArray data, QString strPrivateKey);
  QByteArray *getAESEncrypt(QByteArray data, QString strKey, int intMode);
  QByteArray *getAESDecrypt(QByteArray data, QString strKey, int intMode);

  int generateRSAKey();
  RSA *getRSAKey();

 private:
  static const int KEY_RAND_LENGTH = 16;   //本地随机密钥长度
  static const int RSA_BIT_LENGTH = 1024;  // RSA 位数长度
  static const int RSA_BLOCK_SIZE = RSA_BIT_LENGTH / 8;  // RSA块大小

  RSA *rsa;
  RSA *rsaPub;
  RSA *rsaPri;
  int test(int);
};

#endif  // CRYPTO_H
