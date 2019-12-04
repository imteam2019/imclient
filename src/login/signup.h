#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include "common/data.h"
#include "common/encrypt.h"

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(QWidget *parent = nullptr);
    ~Signup();

private slots:
    void on_pbOk_clicked();

    void on_pbCancel_clicked();

private:
    Ui::Signup *ui;
    QString checkInput();
};

#endif // SIGNUP_H
