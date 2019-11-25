#include "newfriend.h"
#include "ui_newfriend.h"
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
