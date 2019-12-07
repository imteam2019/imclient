#include "encrypt.h"

#include <stdio.h>
#include <string.h>
Encrypt::Encrypt() {}

/**
 * @brief Encrypt::getRandKey 获取本地随机密钥字符串
 * @return
 */
QString Encrypt::getRandKey() {
  // ASCII表中可显示字符的ascii值范围从32-126，其中包含数字、大写字母、小写字母和其他可显示字符（如：@#$%^&*:等）
  // 随机数字在以上范围选择即可
  char key[Encrypt::KEY_RAND_LENGTH];
  qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

  for (int i = 0; i < Encrypt::KEY_RAND_LENGTH; i++) {
    key[i] = (qrand() % (126 - 32)) + 32;
  }

  qDebug() << QString(key) << endl;

  return QString(key);
}

/**
 * @brief Encrypt::encrypt
 * @param byteMsg
 * @return QByteArray *
 * 加密后的QByteArray指针，如入参为空指针或无数据，则返回空指针；
 * @desc
 * 对Byte类型的消息进行加密，该类型包括非字符型的二进制数据，如音频视频等,也可以是某一段内存空间；
 */
QByteArray *Encrypt::encrypt(const QByteArray *byteMsg) {
  QByteArray *enc = nullptr;
  if (byteMsg && byteMsg->size() > 0) {
    // todo: 此处new QByteArray对象，分配给enc，并实现加密算法
  }
  return enc;
}

/**
 * @brief Encrypt::encrypt
 * @param strMsg
 * @return QString * 加密后的QString指针，
 * 如入参为空指针或无数据，则返回空指针；
 * @desc 对QString类型的消息进行加密，纯文本类型；
 */
QString *Encrypt::encrypt(const QString *strMsg) {
  QString *enc = nullptr;
  if (strMsg && strMsg->length() > 0) {
    // todo:此处new QString对象，分配给enc，并实现加密算法
    //可以转化后调用QByteArray * Encrypt::encrypt(const QByteArray *)
  }
  return enc;
}

/**
 * @brief Encrypt::encrypt
 * @param byteMsg
 * @return QByteArray *
 * 解密后的QByteArray指针，如入参为空指针或无数据，则返回空指针；
 * @desc
 * 对Byte类型的密文进行解密，该类型包括非字符型的二进制数据，如音频视频等,也可以是某一段内存空间；
 */
QByteArray *Encrypt::decrypt(const QByteArray *byteMsg) {
  QByteArray *dec = nullptr;
  if (byteMsg && byteMsg->size() > 0) {
    // todo: 此处new QByteArray对象，分配给dec，并实现解密算法
  }
  return dec;
}

/**
 * @brief Encrypt::encrypt
 * @param strMsg
 * @return QString * 加密后的QString指针，
 * 如入参为空指针或无数据，则返回空指针；
 * @desc 对QString类型的消息进行加密，纯文本类型；
 */
QString *Encrypt::decrypt(const QString *strMsg) {
  QString *dec = nullptr;
  if (strMsg && strMsg->length() > 0) {
    // todo:此处new QString对象，分配给enc，并实现解密算法
    //可以转化后调用QByteArray * Encrypt::decrypt(const QByteArray *)
  }
  return dec;
}

QString Encrypt::getMD5(QByteArray data) {
  size_t length = (size_t)data.length();
  if (0 == length) return "";

  MD5_CTX c;
  unsigned char md5[16];

  memset(md5, 0, sizeof(md5));
  MD5_Init(&c);
  MD5_Update(&c, data.data(), length);
  MD5_Final(md5, &c);
  QByteArray *s = new QByteArray((char *)md5, 16);
  qDebug() << s->toHex();

  return QString(*s);
}

/**
 * @brief Encrypt::getRSA 按照指定的公钥字符串，对数据进行RSA加密
 * @param data 待加密的明文内容
 * @param strPublicKey 用于加密的公钥
 * @return 返回包含密文的QByteArray指针，如果出错则为空指针
 */
QByteArray *Encrypt::getRSAEncrypt(QByteArray data, QString strPublicKey) {
  RSA *rsa = nullptr;
  BIO *bioPK = nullptr;
  unsigned char *bufEncrypt = nullptr;
  size_t lenRSA = 0;
  int lenEncryped = 0;

  if (0 == data.length() || 0 == strPublicKey.length()) {
    return nullptr;
  }

  qDebug() << strPublicKey << endl;
  //读取公钥,生成RSA结构体
  bioPK = BIO_new_mem_buf(strPublicKey.toLocal8Bit().data(), -1);
  if (bioPK == nullptr) {
    qDebug() << "Failed to read Public Key from: \n" + strPublicKey << endl;
    return nullptr;
  }

  rsa = PEM_read_bio_RSA_PUBKEY(bioPK, &rsa, nullptr, nullptr);

  // RSA_print_fp(stdout, rsa, 0);

  //初始化密文缓冲区
  lenRSA = (size_t)RSA_size(rsa);
  bufEncrypt = (unsigned char *)malloc(lenRSA + 1);
  memset(bufEncrypt, '\0', lenRSA + 1);

  // 执行公钥加密
  lenEncryped = RSA_public_encrypt(lenRSA, (unsigned char *)data.data_ptr(),
                                   bufEncrypt, rsa, RSA_NO_PADDING);
  RSA_free(rsa);

  if (lenEncryped < 0) return nullptr;

  QByteArray *b = new QByteArray((char *)bufEncrypt, lenEncryped);
  qDebug() << b->toHex() << endl;
  return b;
}

QByteArray *Encrypt::getRSADecrypt(QByteArray data, QString strPrivateKey) {
  if (0 == data.length() || 0 == strPrivateKey.length()) {
    return nullptr;
  }
  // todo 私钥解密处理
  return nullptr;
}
