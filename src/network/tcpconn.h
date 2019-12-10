#ifndef TCPCONN_H
#define TCPCONN_H
/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Network Connection module of the IM Toolkit.
** It support TCP,UDP and HTTP.
**
** Created by: Shengbo.Zeng
** Created date: 12/5/2019
**
**
**
****************************************************************************/
#include <QObject>

class TCPConn : public QObject {
 public:
  TCPConn();
  ~TCPConn();
};

#endif  // TCPCONN_H
