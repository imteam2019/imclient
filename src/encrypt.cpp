#include "encrypt.h"

Encrypt::Encrypt()
{

}

/**
 * @brief Encrypt::encrypt
 * @param byteMsg
 * @return QByteArray * 加密后的QByteArray指针，如入参为空指针或无数据，则返回空指针；
 * @desc 对Byte类型的消息进行加密，该类型包括非字符型的二进制数据，如音频视频等,也可以是某一段内存空间；
 */
QByteArray * Encrypt::encrypt(const QByteArray *byteMsg){
    QByteArray * enc=nullptr;
    if(byteMsg && byteMsg->size()>0) {
       //todo: 此处new QByteArray对象，分配给enc，并实现加密算法
    }
    return enc;
}

/**
 * @brief Encrypt::encrypt
 * @param strMsg
 * @return QString * 加密后的QString指针， 如入参为空指针或无数据，则返回空指针；
 * @desc 对QString类型的消息进行加密，纯文本类型；
 */
QString * Encrypt::encrypt(const QString * strMsg){
    QString * enc=nullptr;
    if(strMsg && strMsg->length()>0){
        //todo:此处new QString对象，分配给enc，并实现加密算法
        //可以转化后调用QByteArray * Encrypt::encrypt(const QByteArray *)
    }
    return enc;
}

/**
 * @brief Encrypt::encrypt
 * @param byteMsg
 * @return QByteArray * 解密后的QByteArray指针，如入参为空指针或无数据，则返回空指针；
 * @desc 对Byte类型的密文进行解密，该类型包括非字符型的二进制数据，如音频视频等,也可以是某一段内存空间；
 */
QByteArray * Encrypt::decrypt(const QByteArray *byteMsg){
    QByteArray * dec=nullptr;
    if(byteMsg && byteMsg->size()>0) {
       //todo: 此处new QByteArray对象，分配给dec，并实现解密算法
    }
    return dec;
}

/**
 * @brief Encrypt::encrypt
 * @param strMsg
 * @return QString * 加密后的QString指针， 如入参为空指针或无数据，则返回空指针；
 * @desc 对QString类型的消息进行加密，纯文本类型；
 */
QString * Encrypt::decrypt(const QString * strMsg){
    QString * dec=nullptr;
    if(strMsg && strMsg->length()>0){
        //todo:此处new QString对象，分配给enc，并实现解密算法
        //可以转化后调用QByteArray * Encrypt::decrypt(const QByteArray *)
    }
    return dec;
}
