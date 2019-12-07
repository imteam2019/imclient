#include "newfriend.h"
#include "ui_newfriend.h"
#include <QMessageBox>
//#include "common/des.h"

NewFriend::NewFriend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewFriend)
{
    ui->setupUi(this);
    ui->tetext->setPlainText("123abc中文到底行不行？");
}

NewFriend::~NewFriend()
{
    delete ui;
}

void NewFriend::on_btnAdd_clicked()
{
    if(ui->leID->text().length()<=0){
        QMessageBox::information(nullptr,"Error:","请输入对方的ID（可能是邮箱地址或电话号码等）。");
        return;
    }

    //todo:此处检索输入的ID，并添加好友的代码实现。
}



void NewFriend::on_btdEn_clicked()
{
    std::string s;
    QString k=ui->leID->text();
    QByteArray kp=k.toLocal8Bit();
    unsigned char * key=(unsigned char * )kp.data();

    QString t=ui->tetext->toPlainText();
    QByteArray tp=t.toLocal8Bit();
    QByteArray *textbase64,textDebase64;

    char * text;

    // 判断是否需要进行base64编码
    textbase64=new QByteArray (tp.toBase64()) ;
    if(ui->cbBase->isChecked()){
        text=textbase64->data();
    }else{
        text=tp.data();
    }

    qDebug()<<QString("原文base64:")<<text<<"\n"<<endl;

    // 加密后显示到界面
    //DES *des=new DES;
    //des->encrypt(key,(unsigned char*)text,des->extend(textbase64->length()));

   // std::string str=(char*)text;
   // ui->teDecrypt->setPlainText(QString::fromLocal8Bit(text,-1));
     qDebug()<<QString("加密后的内容：\n")<<endl;
    qDebug()<<text<<"\n"<<endl;


    //解密后显示到界面
    //des->decrypt(key,(unsigned char*)text,des->extend(textbase64->length()));

    qDebug()<<QString("解密后的内容：\n")<<endl;
     qDebug()<<text<<"\n"<<endl;

     QByteArray qt=QByteArray::fromBase64(*textbase64);
    if(ui->cbBase->isChecked()){
       // s=base64_decode((new QByteArray((const char*)text))->toStdString());

       text=qt.data();
    }

    qDebug()<<"解密后Base64解码："<<text<<endl;

  // ui->teback->setPlainText(QString::fromLocal8Bit(text,-1));

}

