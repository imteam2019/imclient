#ifndef SIGNIN_H
#define SIGNIN_H

/****************************************************************************
**
** Copyright (C)
** Contact:
**
** This file is part of the Authenticate module of the IM Toolkit.
**
** Created by: Shengbo.Zeng
** Created date: 11/24/2019
**
**
**
****************************************************************************/
#include <QDialog>

namespace Ui {
class Signin;
}

class Signin : public QDialog
{
    Q_OBJECT

public:
    explicit Signin(QWidget *parent = nullptr);
    ~Signin();

private slots:

    void on_btnOK_clicked();

private:
    Ui::Signin *ui;
};

#endif // AUTHENTICATE_H
