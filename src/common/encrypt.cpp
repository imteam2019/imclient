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
  char key[Encrypt::KEY_RAND_LENGTH + 1];
  memset(key, '\0', Encrypt::KEY_RAND_LENGTH + 1);
  qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

  for (int i = 0; i < Encrypt::KEY_RAND_LENGTH; i++) {
    key[i] = (qrand() % (126 - 32)) + 32;
  }

  QString b = QString(key);
  qDebug() << "=========getRandKey()===========" << endl;
  qDebug() << "rand key lengh is :\t" << b.length() << endl << b << endl;

  return b;
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
  // qDebug() << s->toHex();

  return QString(*s);
}

QByteArray *Encrypt::getRSAEncrypt(QByteArray data) {
  unsigned char *bufPlain;
  unsigned char *bufEncrypt;
  int lenEncryped = 0;
  size_t lenRSA = 0;
  size_t lenPlain = 0;
  size_t slic = 0;
  lenPlain = (size_t)data.length();
  bufPlain = (unsigned char *)malloc(lenPlain);
  memset(bufPlain, '\0', lenPlain);
  memcpy(bufPlain, data.data(), lenPlain);

  lenRSA = (size_t)RSA_size(rsa);

  if (lenPlain / 117 * 117 == lenPlain) {
    slic = lenPlain / 117;
  } else {
    slic = lenPlain / 117 + 1;
  }

  bufEncrypt = (unsigned char *)malloc(lenRSA * slic);
  memset(bufEncrypt, '\0', lenRSA * slic);

  for (size_t i = 0, clen = 0; i < slic; i++) {
    clen = (slic != i + 1) ? 117 : lenPlain - (117 * i);
    lenEncryped =
        RSA_public_encrypt(clen, bufPlain + 117 * i, bufEncrypt + lenRSA * i,
                           this->rsa, RSA_PKCS1_PADDING);
  }
  // lenEncryped = RSA_public_encrypt(strlen((char *)bufPlain), bufPlain,
  //                                 bufEncrypt, this->rsa, RSA_PKCS1_PADDING);

  if (lenEncryped < 0) {
    //加载错误信息
    ERR_load_ERR_strings();
    ERR_load_crypto_strings();
    // 获取错误号
    unsigned long ulErr = ERR_get_error();
    char szErrMsg[1024] = {0};
    char *pTmp = nullptr;
    // 格式：error:errId:库:函数:原因
    pTmp = ERR_error_string(ulErr, szErrMsg);
    qDebug() << "error is :" << endl << pTmp << endl;
    qDebug() << "data is : " << endl << data.data() << endl;
    return nullptr;
  }
  /*
    qDebug() << "=============getRSAEncrypt==========" << endl;
    qDebug() << "before encryption:" << endl << data.data() << endl;
    qDebug() << "after encryption:" << endl;
    for (int i = 0; i < lenEncryped; i++) {
      printf("%02X", bufEncrypt[i]);
    }
    printf("\n\n");
  */
  QByteArray *b = new QByteArray((char *)bufEncrypt, lenRSA * slic);
  // return b;
  /*
    unsigned char *buf;
    buf = (unsigned char *)malloc(lenPlain + 1);
    memset(buf, '\0', lenPlain + 1);
    int bufl = 0;
    for (size_t i = 0; i < slic; i++) {
      int j = RSA_private_decrypt(128, bufEncrypt + (i * 128), buf + (i * 117),
                                  this->rsa, RSA_PKCS1_PADDING);
      //    qDebug() << "j :\t" << j << endl;
      bufl += j;
    }
    // int j = RSA_private_decrypt(lenEncryped, bufEncrypt, buf, this->rsa,
    //                            RSA_PKCS1_PADDING);
    printf("\n=======print decrypt info========\n");
    //  qDebug() << "\n bufl = " << bufl << endl;
    for (int i = 0; i <= bufl; i++) {
      printf("%c", buf[i]);
    }
    printf("\n");
  */
  // QByteArray *b = new QByteArray((char *)buf, bufl);
  return b;
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
                                   bufEncrypt, rsa, RSA_PKCS1_OAEP_PADDING);
  RSA_free(rsa);

  if (lenEncryped < 0) return nullptr;

  QByteArray *b = new QByteArray((char *)bufEncrypt, lenEncryped);
  qDebug() << b->toHex() << endl;
  return b;
}

/**
 * @brief Encrypt::getRSADecrypt
 * 私钥解密，对RSA的对应API进行了封装，支持任意长度内容的密文解密，同时为避免对原始密文的误操作，将原始密文复制到新的缓冲区进行后续处理。
 * @param QByteArray data 保存密文的QByteArray对象实例
 * @return QByteArray * 保存解密后内容的QByteArray *指针，如出错则为空指针
 */
QByteArray *Encrypt::getRSADecrypt(QByteArray data) {
  if (0 == data.length()) {
    return nullptr;
  }

  unsigned char *bufPlain;  //存放解密后内容的缓冲区
  unsigned char *
      bufEncrypt;  //为避免修改原文缓冲区数据，定义新的缓冲区，并将原密文复制过来
  size_t lenEncrypted = (size_t)data.length();  //密文长度
  size_t slic = 0;                              //密文块数
  size_t lenPlain = 0;                          //解密后内容长度
  size_t lenRSA = (size_t)RSA_size(this->rsa);

  // 按原密文长度分配新的密文缓冲区内存，以'\0'填充，并复制原密文副本
  bufEncrypt = (unsigned char *)malloc(lenEncrypted);
  memset(bufEncrypt, '\0', lenEncrypted);
  memcpy(bufEncrypt, data.data(), lenEncrypted);

  // 计算密文块数，为rsa长度的整数倍
  if (lenEncrypted / lenRSA * lenRSA == lenEncrypted) {
    slic = lenEncrypted / lenRSA;
  } else {
    slic = lenEncrypted / lenRSA + 1;
  }

  // 估算原明文的内容长度，并分配缓冲区，以'\0'填充
  // 为确保解密后内容准确，缓冲区长度加1
  lenPlain = 117 * slic;
  bufPlain = (unsigned char *)malloc(lenPlain + 1);
  memset(bufPlain, '\0', lenPlain + 1);

  // 按块数利用私钥进行循环解密，并进行拼接
  for (size_t i = 0; i < slic; i++) {
    int j =
        RSA_private_decrypt(lenRSA, bufEncrypt + (i * lenRSA),
                            bufPlain + (i * 117), this->rsa, RSA_PKCS1_PADDING);
  }

  // 逐字输出解密缓冲区内的数据
  for (size_t i = 0; i <= lenPlain; i++) {
    printf("%c", bufPlain[i]);
  }
  printf("\n");

  QByteArray *b = new QByteArray((char *)bufPlain, (int)lenPlain);
  return b;
}

int Encrypt::generateRSAKey() {
  if (this->rsa != nullptr) RSA_free(this->rsa);
  // if (this->rsaPri != nullptr) RSA_free(this->rsaPri);
  // if (this->rsaPub != nullptr) RSA_free(this->rsaPub);
  this->rsa = RSA_new();
  int ret = 0;
  BIGNUM *bne = BN_new();
  ret = BN_set_word(bne, RSA_F4);
  ret = RSA_generate_key_ex(this->rsa, Encrypt::RSA_BIT_LENGTH, bne, nullptr);

  // this->rsaPub = RSAPublicKey_dup(this->rsa);
  // this->rsaPri = RSAPrivateKey_dup(this->rsa);
  return 0;
}

int Encrypt::test(int intBitLength) {
  RSA *rsa = RSA_new();
  int ret = 0;
  BIGNUM *bne = BN_new();
  ret = BN_set_word(bne, RSA_F4);
  ret = RSA_generate_key_ex(rsa, 1024, bne, nullptr);

  unsigned char bufPlain[1024] = {0};
  //"Returns the attribute associated with the code code.";
  QString s = Encrypt::getRandKey();
  memcpy(bufPlain, s.toLocal8Bit(), s.toLocal8Bit().length());
  unsigned char bufEncrypt[1024] = {0};
  unsigned char bufDecrypt[1024] = {0};
  int outl = 1024;
  int outl2;
  int j = (int)strlen((char *)bufPlain);
  printf("%s\n", bufPlain);
  for (size_t i = 0; i < j; i++) {
    printf("%02x ", bufPlain[i]);
  }
  printf("\n---------------\n");

  RSA *rpub = RSAPublicKey_dup(rsa);
  RSA *rpri = RSAPrivateKey_dup(rsa);

  outl = RSA_public_encrypt(strlen((char *)bufPlain), bufPlain, bufEncrypt,
                            rpub, RSA_PKCS1_OAEP_PADDING);
  for (int i = 0; i < outl; i++) {
    printf("%02x ", bufEncrypt[i]);
    if ((i + 1) % 10 == 0) printf("\n");
  }
  printf("\n");
  outl2 = RSA_private_decrypt(outl, bufEncrypt, bufDecrypt, rpri,
                              RSA_PKCS1_OAEP_PADDING);
  printf("-----------------\n%s\n", bufDecrypt);
  for (int i = 0; i < outl2; i++) {
    printf("%02x ", bufDecrypt[i]);
  }
  printf("\n");
  RSA_free(rsa);
  return 0;
}

QByteArray *Encrypt::getAESEncrypt(QByteArray data, QString strKey,
                                   int intMode = 0) {
  // 检查入参，如果数据为空，或者加密Key不为16的整数倍，则返回空指针
  // TODO 考虑到性能，此处应该对key的最大长度作出限制，具体限制长度后续再定
  if (data.length() <= 0) return nullptr;
  if (0 == strKey.length() || strKey.length() % AES_BLOCK_SIZE != 0)
    return nullptr;

  // printf("===========entry getAESEncrypt()==========");
  AES_KEY aes;
  unsigned char *key = nullptr;      // AES_BLOCK_SIZE = 16
  unsigned char iv[AES_BLOCK_SIZE];  // init vector
  unsigned char *bufPlain = nullptr;
  unsigned char *bufEncrypt = nullptr;
  unsigned char *bufDecrypt = nullptr;
  size_t len;  // encrypt length (in multiple of AES_BLOCK_SIZE)
  size_t lenPlain = (size_t)data.length();
  size_t i, lenKey = (size_t)strKey.length();

  // set the encryption length
  len = 0;
  if (lenPlain % AES_BLOCK_SIZE == 0) {
    len = lenPlain + 1;
  } else {
    len = ((lenPlain + 1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
  }

  // set the input string
  bufPlain = (unsigned char *)malloc(len);
  if (bufPlain == nullptr) {
    qDebug() << "Unable to allocate memory for bufPlain." << endl;
    return nullptr;
  }
  memset(bufPlain, '\0', len);
  memcpy(bufPlain, data.data(), lenPlain);

  // 设置key
  key = (unsigned char *)malloc(lenKey);
  memset(key, '\0', lenKey);
  memcpy(key, strKey.toLocal8Bit(), lenKey);

  // Set encryption key
  for (i = 0; i < AES_BLOCK_SIZE; ++i) {
    iv[i] = 0;
  }
  if (AES_set_encrypt_key(key, (int)lenKey * 8, &aes) < 0) {
    qDebug() << "Unable to set encryption key in AES\n" << endl;
    return nullptr;
  }

  // alloc encrypt_string
  bufEncrypt = (unsigned char *)malloc(len);
  if (bufEncrypt == nullptr) {
    qDebug() << "Unable to allocate memory for encrypt_string\n" << endl;
    return nullptr;
  }
  memset(bufEncrypt, '\0', len);

  // encrypt (iv will change)
  AES_cbc_encrypt(bufPlain, bufEncrypt, len, &aes, iv, AES_ENCRYPT);
  /*
  qDebug() << "=============getAESEncrypt==========" << endl;
  qDebug() << "before encryption:" << endl << data.data() << endl;
  qDebug() << "after encryption:" << endl;

  printf("AES encrypted string = ");
  for (i = 0; i < len; ++i) {
    printf("%x%x", (bufEncrypt[i] >> 4) & 0xf, bufEncrypt[i] & 0xf);
  }

  printf("\n");
/*
  QByteArray *e = new QByteArray((char *)bufEncrypt, len);

  return e;

  /*
  // alloc decrypt_string
  bufDecrypt = (unsigned char *)malloc(len);
  if (bufDecrypt == nullptr) {
    qDebug() << "Unable to allocate memory for decrypt_string\n" << endl;
    return nullptr;
  }

  // Set decryption key
  for (i = 0; i < AES_BLOCK_SIZE; ++i) {
    iv[i] = 0;
  }
  if (AES_set_decrypt_key(key, (int)lenKey * 8, &aes) < 0) {
    qDebug() << "Unable to set decryption key in AES\n" << endl;
    return nullptr;
  }

  // decrypt
  AES_cbc_encrypt(bufEncrypt, bufDecrypt, len, &aes, iv, AES_DECRYPT);

  printf("encrypted string = ");
  for (i = 0; i < len; ++i) {
    printf("%x%x", (bufEncrypt[i] >> 4) & 0xf, bufEncrypt[i] & 0xf);
  }

  printf("\n");
  printf("decrypted string = ");
  for (i = 0; i < len; ++i) {
    printf("%c", bufDecrypt[i]);
  }
  printf("\n");

  return nullptr;
  */
}

QByteArray *Encrypt::getAESDecrypt(QByteArray data, QString strKey,
                                   int intMode) {
  // 检查入参，如果数据为空，或者加密Key不为16的整数倍，则返回空指针
  // TODO 考虑到性能，此处应该对key的最大长度作出限制，具体限制长度后续再定
  if (data.length() <= 0) return nullptr;
  if (0 == strKey.length() || strKey.length() % AES_BLOCK_SIZE != 0)
    return nullptr;
  // printf("===========entry getAESDecrypt()==========");
  AES_KEY aes;
  unsigned char *key = nullptr;      // AES_BLOCK_SIZE = 16
  unsigned char iv[AES_BLOCK_SIZE];  // init vector
  // unsigned char *bufPlain = nullptr;
  unsigned char *bufEncrypt = nullptr;
  unsigned char *bufDecrypt = nullptr;
  size_t lenEncrypt = (size_t)data.length();  // encrypted data length
  // size_t lenPlain = (size_t)data.length();
  size_t i, lenKey = (size_t)strKey.length();

  // 设置密文缓冲区，并创建副本
  bufEncrypt = (unsigned char *)malloc(lenEncrypt + 1);
  if (bufEncrypt == nullptr) {
    qDebug() << "Unable to allocate memory for bufEncrypt." << endl;
    return nullptr;
  }
  memset(bufEncrypt, '\0', lenEncrypt + 1);
  memcpy(bufEncrypt, data.data(), lenEncrypt);

  // 设置明文缓冲区，为确保数据完整，长度为密文长度+1
  bufDecrypt = (unsigned char *)malloc(lenEncrypt + 1);
  if (bufEncrypt == nullptr) {
    qDebug() << "Unable to allocate memory for bufEncrypt." << endl;
    return nullptr;
  }
  memset(bufDecrypt, '\0', lenEncrypt + 1);

  // 设置key
  key = (unsigned char *)malloc(lenKey);
  memset(key, '\0', lenKey);
  memcpy(key, strKey.toLocal8Bit(), lenKey);

  // 初始化iv,并根据密钥初始化aes
  for (i = 0; i < AES_BLOCK_SIZE; ++i) {
    iv[i] = 0;
  }
  if (AES_set_decrypt_key(key, (int)lenKey * 8, &aes) < 0) {
    qDebug() << "Unable to set decryption key in AES\n" << endl;
    return nullptr;
  }

  // decrypt
  AES_cbc_encrypt(bufEncrypt, bufDecrypt, lenEncrypt, &aes, iv, AES_DECRYPT);

  /*
  printf("decrypted string = ");
  for (i = 0; i < lenEncrypt; ++i) {
    printf("%c", bufDecrypt[i]);
  }
  printf("\n");
*/
  return nullptr;
}
