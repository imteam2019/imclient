#include "httpconn.h"

HTTPConn::HTTPConn() {
  this->manager = new QNetworkAccessManager(this);
  QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), this,
                   SLOT(replyFinished(QNetworkReply *)));
  this->qr = nullptr;
  this->qUrl = nullptr;
  this->request = nullptr;
}

HTTPConn::~HTTPConn() {
  // delete this->qr;
  // delete this->qUrl;
  delete this->manager;
}

bool HTTPConn::get() {
  if (this->request != nullptr) {
    delete this->request;
  }
  this->request = new QNetworkRequest(*this->qUrl);
  this->qr = this->manager->get(*this->request);

  // printf("\n===========get()===============\n");
  // this->printRequestHeasers(this->request);

  if (this->qr != nullptr) {
    return true;
  } else {
    return false;
  }
}

bool HTTPConn::post(QString strData) {
  if (this->request != nullptr) {
    delete this->request;
  }
  this->request = new QNetworkRequest(*this->qUrl);

  //        this->request->setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
  this->request->setRawHeader(
      "Accept", "application/json,text/html, application/xhtml+xml, */*");
  //        this->request->setRawHeader("Referer",this->qUrl->toString().toUtf8());
  //        this->request->setRawHeader("Accept-Language","zh-CN");
  //        this->request->setRawHeader("X-Requested-With","XMLHttpRequest");
  this->request->setRawHeader(
      "User-Agent",
      "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)");
  // this->request->setRawHeader("Content-Type",
  //                           "application/x-www-form-urlencoded");
  //        this->request->setRawHeader("Accept-Encoding","gzip,deflate");
  //        this->request->setRawHeader("Host",this->URL().toUtf8());
  //         this->request->setRawHeader("Content-Length",QByteArray(strData.toUtf8().length(),10));
  this->request->setRawHeader("Connection", "Keep-Alive");
  this->request->setRawHeader("Cache-Control", "no-cache");

  this->request->setRawHeader("Content-Type", "application/json");

  printf("\n===========Post()===============\n");
  this->printRequestHeasers(this->request);
  this->qr = this->manager->post(*this->request, strData.toUtf8());
  printf("\n===========end Post()===============\n");
  // this->printRequestHeasers(this->request);

  if (this->qr != nullptr) {
    // this->qr->res
    return true;
  } else {
    return false;
  }
}

/**
 * @brief HTTPConn::setURL 指定访问的url地址
 * @param strUrl 合法的url地址字符串
 */
void HTTPConn::setURL(QString strUrl) {
  if (strUrl.length() > 0) {
    if (this->qUrl != nullptr) delete this->qUrl;
    this->qUrl = new QUrl(strUrl);
  }
}

/**
 * @brief HTTPConn::URL 获取当前链接指向的url地址
 * @return url地址字符串，如果为nullptr,则返回空字符串
 */
QString HTTPConn::URL() { return this->qUrl->toString(); }

void HTTPConn::registCallBack(PFUNC pfunn, void *pUser) {
  this->pf = pfunn;
  this->pUesr = pUser;
}

void HTTPConn::getData(PFUNC pfun, int rePlyFlag, QString strData,
                       void *pUser) {
  if ("" != strData) {
    pfun(strData, rePlyFlag, pUesr);
  } else {
    pfun(strData, rePlyFlag, pUser);
  }
}

/**
 * @brief HTTPConn::replyFinished
 * 服务器响应结束后的数据处理，按照返回状态调用回调函数
 * @param reply QNetworkReply指针
 */
void HTTPConn::replyFinished(QNetworkReply *reply) {
  this->printResponseHeaders(reply);
  QTextCodec *codec = QTextCodec::codecForName("utf8");
  QString all;
  int intHttpStatusCode =
      reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  QString strHttpStatusMessage =
      reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();

  if (reply->error()) {
    all = reply->errorString();
    this->getData(this->pf, HTTPConn::RESP_FAILED, all, this->pUesr);
    qDebug() << all << endl;
  }
  if (intHttpStatusCode == HTTPConn::HttpResponseStatus::HTTPStatusOK) {
    all = codec->toUnicode(reply->readAll());
    this->getData(this->pf, intHttpStatusCode, all, this->pUesr);
    qDebug() << all << endl;
  } else {
    this->getData(this->pf, intHttpStatusCode, strHttpStatusMessage,
                  this->pUesr);
    qDebug() << strHttpStatusMessage << endl;
  }

  reply->deleteLater();
}

/**
 * @brief HTTPConn::printRequestHeasers 输出客户端http请求时的headers
 * @param request QNetworkRequest指针
 */
void HTTPConn::printRequestHeasers(QNetworkRequest *request) {
  QList<QByteArray> s = request->rawHeaderList();
  qDebug() << "============Print Request Headers Info==========" << endl;
  qDebug() << this->qUrl->toString() << endl;
  for (int i = 0; i < s.size(); i++) {
    qDebug() << s.at(i) << ":\t" << request->rawHeader(s.at(i)) << endl;
  }
  qDebug() << "============End Request Headers Info==========" << endl;
}

/**
 * @brief HTTPConn::printResponseHeaders 输出服务器http响应的headers
 * @param reply
 */
void HTTPConn::printResponseHeaders(QNetworkReply *reply) {
  QList<QByteArray> s = reply->rawHeaderList();
  qDebug() << "============Print Response Headers Info==========" << endl;
  // qDebug()<<this->qUrl->toString()<<endl;
  for (int i = 0; i < s.size(); i++) {
    qDebug() << s.at(i) << ":\t" << reply->rawHeader(s.at(i)) << endl;
  }
  qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()
           << endl;
  qDebug() << "============End Response Headers Info==========" << endl;
}
