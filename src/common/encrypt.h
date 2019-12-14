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
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>

#include <QByteArray>
#include <QString>
#include <QTime>
#include <iostream>
#include <ostream>

#include "openssl/aes.h"
#include "openssl/des.h"
#include "openssl/err.h"
#include "openssl/md5.h"
#include "openssl/rsa.h"
#include "openssl/ssl.h"

using namespace std;
class Encrypt {
 public:
  Encrypt();
  std::string *encrypt(const std::string *);
  QByteArray *encrypt(const QByteArray *);
  QByteArray *decrypt(const QByteArray *);
  std::string *decrypt(const std::string *);
  std::string getMD5(std::string *data, unsigned int len);
  // static QString getBase64(QByteArray data);
  std::string getRandKey();
  QByteArray *getRSAEncrypt(QByteArray data);
  QByteArray *getRSAEncrypt(QByteArray data, std::string strPublicKey);
  QByteArray *getRSADecrypt(QByteArray data);
  QByteArray *getRSADecrypt(QByteArray data, std::string strPrivateKey);
  QByteArray *getAESEncrypt(QByteArray data, std::string strKey, int intMode);
  QByteArray *getAESDecrypt(QByteArray data, std::string strKey, int intMode);

  static std::string *getBase64Encode(const char *buffer, long long length,
                                      bool newLine);
  static std::string *getBase64Decode(const char *buffer, long long length,
                                      bool newLine);

  int generateRSAKey();
  RSA *getRSAKey();

 private:
  static const int KEY_RAND_LENGTH = 16;   //本地随机密钥长度
  static const int RSA_BIT_LENGTH = 1024;  // RSA 位数长度
  static const int RSA_BLOCK_SIZE = RSA_BIT_LENGTH / 8;  // RSA块大小

  RSA *rsa;
  RSA *rsaPub;
  RSA *rsaPri;
};

#endif  // CRYPTO_H
