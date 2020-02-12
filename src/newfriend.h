#ifndef NEWFRIEND_H
#define NEWFRIEND_H

/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Add New Friend module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/25/2019
**
**
**
****************************************************************************/
#include <QDialog>
#include <QtDebug>
#include <iostream>

using namespace std;

namespace Ui {
class NewFriend;
}

class NewFriend : public QDialog {
  Q_OBJECT

 public:
  explicit NewFriend(QWidget *parent = nullptr);
  ~NewFriend();

 private slots:
  void on_btnAdd_clicked();
  void on_btdEn_clicked();

 private:
  Ui::NewFriend *ui;
};

#endif  // NEWFRIEND_H
