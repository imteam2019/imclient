#include "tcpconn.h"

TCPConn::TCPConn() {
  this->ts = new QTcpSocket(this);
  this->msgSendQueue = new QQueue<Message>();
  this->msgReceiveQueue = new QQueue<Message>();
  connect(this->ts, SIGNAL(connected()), this, SLOT(doConnected()));
  connect(this->ts, SIGNAL(error(QAbstractSocket::SocketError)), this,
          SLOT(doError(QAbstractSocket::SocketError)));
  connect(this->ts, SIGNAL(disconnected()), this, SLOT(doDisconnected()));
  connect(this->ts, SIGNAL(bytesWritten(long long)), this,
          SLOT(bytesWritten(long long)));
  connect(this->ts, SIGNAL(readyRead()), this, SLOT(doReadyRead()));
  // connect(this->msgSendQueue, SIGNAL(newArrival()), this, SLOT(doSend()));
#ifdef MY_DEBUG_ON
  std::cout << "当前处于调试状态." << endl;
#else
  std::cout << "调试开关已关闭" << endl;
#endif
  this->loadQueueFromFile();
  this->ts->connectToHost("47.88.231.69", 8000, QAbstractSocket::ReadWrite);
}

TCPConn::~TCPConn() {
  this->ts->close();
  this->savaQueueToFile();
  this->msgSendQueue->clear();
  this->msgReceiveQueue->clear();
  this->ts->deleteLater();
}

/**
 * @brief TCPConn::savaQueueToFile 将当前队列中尚未处理的数据写入本地文件
 * @return 返回写入文件的字节数,出错则为-1
 */
long long TCPConn::savaQueueToFile() {
  // TODO
  return 0;
}

/**
 * @brief TCPConn::loadQueueFromFile
 * 将上次程序关闭尚未处理完毕的消息恢复到队列中
 * @return 加载数据的字节数，出错则为-1
 */
long long TCPConn::loadQueueFromFile() {
  // TODO
  return 0;
}

void TCPConn::bytesWritten(long long len) {
  std::cout << "bytesWritten size:\t" << len << endl;
  return;
}

/**
 * @brief TCPConn::sendMessage
 * @param m 待发送的Message对象
 * @return long long 返回发送的数据长度，如失败则为-1
 */
long long TCPConn::sendMessage(Message &m) {
  // TODO 判断消息当前的已发送次数
  this->msgSendQueue->enqueue(m);
  emit prepareSendArrival();
  return 0;
}

/**
 * @brief TCPConn::sendMessage 发送缓冲区指定长度的字节数据
 * @param data 待发送缓冲区指针
 * @param len 待发送的数据长度
 */
void TCPConn::sendMessage(std::string *data, unsigned int len) {
  long long i = this->ts->write(data->c_str(), len);
#ifdef MY_DEBUG_ON
  std::cout << "Data size:\t" << len << endl;
  std::cout << "Send size:\t" << i << endl;
  std::cout << *data << endl;
#endif
}

/**
 * @brief TCPConn::doConnected Tcp
 * Socket与服务端链接成功后，输出对应的服务器地址、端口和名称信息
 */
void TCPConn::doConnected() {
#ifdef MY_DEBUG_ON
  // std::cout << this->ts->peerAddress() << ":" << this->ts->peerPort() << ":"
  //          << this->ts->peerName() << endl;
  std::cout << this->ts->state();
#endif
  return;
}
void TCPConn::doDisconnected() {
  std::cout << "In doDisconnected()" << endl;
  return;
}
void TCPConn::doReadyRead() {
  std::cout << "In doReadRead()" << endl;
  return;
}
void TCPConn::doFinishRead(Message &m) {
  std::cout << "In doFinishRead()" << endl;
  std::cout << this->ts->readAll().data() << endl;
  return;
}
/**
 * @brief TCPConn::doReadySend 当Tcp
 * Socket进入准备发送状态时，从发送队列中获取消息对象并发送数据。
 * 如果发送队列为空，则什么也不做。
 */
void TCPConn::doReadySend() {
  std::cout << "In doReadSend()" << endl;
  while (this->msgSendQueue->size() > 0) {
    this->msgSendQueue->dequeue();
  }
  return;
}
void TCPConn::doFinishSend() {
  std::cout << "In doFinishSend()" << endl;
  return;
}
void TCPConn::doError(QAbstractSocket::SocketError socketErr) {
  std::cout << "network error." << socketErr << endl;
  return;
}
void TCPConn::doQueueEmpty(QQueue<Message> &e) {}

/**
 * @brief TCPConn::doSend 发送Message实例数据。如果成功则返回，否则，计数器减1。
 */
void TCPConn::doSend() {
  // 将消息发送队列中的数据写入Tcp Socket发送
  Message m = this->msgSendQueue->dequeue();
  // std::string *s = m.toJSON();
  long long i = this->ts->write(nullptr, m.getMsgSize());
#ifdef MY_DEBUG_ON
  std::cout << "Msg  size:\t" << m.getMsgSize() << endl;
  std::cout << "Send size:\t" << i << endl;

#endif
}

void TCPConn::registCallback(PNEWMESSAGE ptrData, void *ptrUser) {
  this->ptrNewMassage = ptrData;
  this->ptrNewMsgHandle = ptrUser;
}
