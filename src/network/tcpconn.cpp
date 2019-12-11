#include "tcpconn.h"

TCPConn::TCPConn() {
  this->ts = new QTcpSocket(this);
  connect(this->ts, SIGNAL(connected()), this, SLOT(doConnected()));
  connect(this->ts, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(doError(QAbstractSocket::SocketError)));
  connect(this->ts, SIGNAL(disconnected()), this, SLOT(doDisconnected()));
  connect(this->ts, SIGNAL(bytesWritten(qint64)), this,
          SLOT(bytesWritten(qint64)));
  connect(this->ts, SIGNAL(readyRead()), this, SLOT(doReadyRead()));
  this->loadQueueFromFile();
  this->ts->connectToHost("47.88.231.69", 8000, QAbstractSocket::ReadWrite);
}

TCPConn::~TCPConn() {
  this->ts->close();
  this->savaQueueToFile();
  this->msgSendQueue.clear();
  this->msgReceiveQueue.clear();
  this->ts->deleteLater();
}

/**
 * @brief TCPConn::savaQueueToFile 将当前队列中尚未处理的数据写入本地文件
 * @return 返回写入文件的字节数,出错则为-1
 */
qint64 TCPConn::savaQueueToFile() {
  QFile fileOut("/Users/anthony.shengbo.zeng/projects/imclient/src/msg.txt");
  if (!fileOut.open(QIODevice::Append | QIODevice::ReadWrite)) {
    qDebug() << tr("无法打开文件:") + fileOut.errorString() << endl;
    return -1;
  }
  QDataStream dsOut(&fileOut);
  dsOut.setVersion(QDataStream::Qt_5_13);
  foreach (Message msg, this->msgSendQueue) { dsOut << msg; }
  fileOut.flush();
  fileOut.close();
  return 0;
}

/**
 * @brief TCPConn::loadQueueFromFile
 * 将上次程序关闭尚未处理完毕的消息恢复到队列中
 * @return 加载数据的字节数，出错则为-1
 */
qint64 TCPConn::loadQueueFromFile() {
  // TODO
  return 0;
}

void TCPConn::bytesWritten(qint64 len) {
  qDebug() << "bytesWritten size:\t" << len << endl;
  return;
}

/**
 * @brief TCPConn::sendMessage 发送Message实例数据
 * @param m 待发送的Message对象
 */
void TCPConn::sendMessage(Message &m) {
  m.getMsgHeader()->sendCount += 1;
  // 测试代码
  this->msgSendQueue.append(m);

  // 将消息写入Tcp Socket发送
  qint64 i = this->ts->write((const char *)m.getMsg(), (qint64)m.getMsgSize());
  qDebug() << "Msg  size:\t" << m.getMsgSize() << endl;
  qDebug() << "Send size:\t" << i << endl;
}

/**
 * @brief TCPConn::sendMessage 发送缓冲区指定长度的字节数据
 * @param data 待发送缓冲区指针
 * @param len 待发送的数据长度
 */
void TCPConn::sendMessage(const char *data, int len) {
  qint64 i = this->ts->write(data, len);
  qDebug() << "Data size:\t" << len << endl;
  qDebug() << "Send size:\t" << i << endl;
}

/**
 * @brief TCPConn::doConnected Tcp
 * Socket与服务端链接成功后，输出对应的服务器地址、端口和名称信息
 */
void TCPConn::doConnected() {
  qDebug() << this->ts->peerAddress().toString() << ":" << this->ts->peerPort()
           << ":" << this->ts->peerName() << endl;
  qDebug() << this->ts->state();
  return;
}
void TCPConn::doDisconnected() {
  qDebug() << "In doDisconnected()" << endl;
  return;
}
void TCPConn::doReadyRead() {
  qDebug() << "In doReadRead()" << endl;
  return;
}
void TCPConn::doFinishRead(Message &m) {
  qDebug() << "In doFinishRead()" << endl;
  qDebug() << this->ts->readAll() << endl;
  return;
}
void TCPConn::doReadySend() {
  qDebug() << "In doReadSend()" << endl;
  return;
}
void TCPConn::doFinishSend() {
  qDebug() << "In doFinishSend()" << endl;
  return;
}
void TCPConn::doError(QAbstractSocket::SocketError socketErr) {
  qDebug() << "network error." << endl;
  return;
}
void TCPConn::doQueueEmpty(QQueue<Message> &e) {}
