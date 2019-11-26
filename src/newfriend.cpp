#include "newfriend.h"
#include "ui_newfriend.h"
#include "descrypt.h"
#include <QMessageBox>

NewFriend::NewFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFriend)
{
    ui->setupUi(this);
}

NewFriend::~NewFriend()
{
    delete ui;
}

void NewFriend::on_btnAdd_clicked()
{
    if(ui->leID->text().length()<=0){
        QMessageBox::information(nullptr,"Error:","请输入对方的ID（可能是数字、邮箱地址或电话号码等）。");
        return;
    }

    //todo:此处检索输入的ID，并添加好友的代码实现。
}

void NewFriend::on_btnEncrypt_clicked()
{
    DesCrypt *Des=new DesCrypt;
    QString Qkey = ui->leID->text();

    QString data= ui->teditleft->toPlainText();
    char *key = ui->leID->text().toLatin1().data();
        Des->setKey(key);
        Des->encrypt(data.toLatin1().data());
        QString endata = QString::fromLocal8Bit(Des->endata.c_str());
        ui->teditright->setPlainText(endata);
}

void NewFriend::on_btnDecrypt_clicked()
{
    DesCrypt *Des=new DesCrypt;
    QString Qkey = ui->leID->text();
        QString data = ui->teditright->toPlainText();
        ui->teditleft->clear();
        QString err = "InputError,please check your input!";
        if(Qkey.isEmpty()||data.isEmpty()){
            ui->teditleft->setPlainText(err);
            return;
        }
        if(Qkey.length()!=8){
            ui->teditright->setPlainText("length of key must be 8!");
            return;
        }

        char *key = Qkey.toLatin1().data();
        Des->setKey(key);
        Des->decrypt(data.toLatin1().data());
        QString dedata = QString::fromLocal8Bit(Des->dedata.c_str());
        ui->teditleft->setPlainText(dedata);

}
