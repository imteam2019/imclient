#ifndef HTTPCONN_H
#define HTTPCONN_H

/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Network Connection module of the IM Toolkit.
** It support HTTP.
**
** Created by: Shengbo.Zeng
** Created date: 12/5/2019
**
**
**
****************************************************************************/
#include <QDebug>
#include <QNetworkAccessManager>
#include <QTextCodec>
#include <QUrl>
#include <QtNetwork>

typedef void (*PFUNC)(QString reply, int replyFlag, void *pObject);

class HTTPConn : public QObject {
 public:
  HTTPConn();
  ~HTTPConn();

  enum HttpResponseStatus { HTTPStatusOK = 200 };

  void setURL(QString strUrl);
  QString URL();
  bool get();
  bool post(QString strData);

  void getData(PFUNC pfun, int rePlyFlag, QString strData, void *pUser);
  void registCallBack(PFUNC pfunn, void *pUser);

  enum enumType { RESP_SUCCESS = 0, RESP_FAILED = 1 };

 private:
  Q_OBJECT
  QNetworkAccessManager *manager;
  QNetworkRequest *request;
  QNetworkReply *qr;
  PFUNC pf;
  void *pUesr;
  QUrl *qUrl;

  // 调试代码
  void printResponseHeaders(QNetworkReply *);
  void printRequestHeasers(QNetworkRequest *);

 private slots:
  void replyFinished(QNetworkReply *);
};

#endif  // CONN_H
