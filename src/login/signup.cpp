#include "signup.h"
#include "ui_signup.h"

Signup::Signup(QWidget *parent) : QDialog(parent),
                                  ui(new Ui::Signup)
{
    ui->setupUi(this);
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_pbOk_clicked()
{
    /**
     * {"username": "yhait",
     * "password": "123456",
     * "instruction": "111111111111111111111111",
     * "telephone": "17775739032",
     * "email": "yaozijian@foxmail.com"}
     */
    QString str = this->checkInput();
    if ("" != str)
    {
        QMessageBox::information(this, "数据输入问题", str);
        return;
    }

    QMap<QString, QVariant> s;
    s.insert("username", ui->leUsername->text());
    s.insert("password", ui->lePasswd->text());
    s.insert("telephone", ui->lePhoneNumber->text());
    s.insert("email", ui->leEmail->text());
    s.insert("instruction", ui->teDesc->toHtml());

    QMessageBox::information(this, "", Data::format(&s, Data::JSON));
}

/**
 * @brief Signup::checkInput 检查界面输入信息是否合法有效
 * @return 如果数据合法有效，则返回空字符串，否则返回错误信息
 */
QString Signup::checkInput()
{
    QString s = "";
    if ((ui->leUsername->text().length()) <= 0)
        s = "请输入你要注册的用户名称。";
    if (ui->lePasswd->text().length() <= 0 || ui->lePasswdRe->text() <= 0)
        s = "密码及验证不能为空。";
    if (ui->lePasswd->text() != ui->lePasswdRe->text())
        s = "两次密码不匹配，请重新输入。";
    if (ui->leEmail->text().length() <= 0)
        s = "请输入你的邮箱地址。";
    if (ui->lePhoneNumber->text().length() <= 0)
        s = "请输入你的电话号码";
    if (ui->teDesc->toPlainText().length() > 100)
        s = "描述信息限制在100个字符以下。";

    return s;
}

void Signup::on_pbCancel_clicked()
{
    this->close();
}
