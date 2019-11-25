#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

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
class Authenticate;
}

class Authenticate : public QDialog
{
    Q_OBJECT

public:
    explicit Authenticate(QWidget *parent = nullptr);
    ~Authenticate();

private slots:

    void on_btnOK_clicked();

private:
    Ui::Authenticate *ui;
};

#endif // AUTHENTICATE_H
