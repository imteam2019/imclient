#include "signup.h"

#include "ui_signup.h"

Signup::Signup(QWidget *parent) : QDialog(parent), ui(new Ui::Signup) {
  ui->setupUi(this);
  //"http://47.88.231.69/MsgServer/publicKey/public.key"
  this->hc = new HTTPConn();
  this->hc->setURL("http://47.88.231.69/MsgServer/publicKey/public.key");
  this->hc->registCallBack(getPublicKey, this);
  if (!this->hc->get()) {
    QMessageBox::information(this, "网络错误",
                             "访问地址出错，请检查网络或地址是否正确。");
  }
}

Signup::~Signup() {
  delete ui;
  delete this->hc;
}

/**
 * @brief Signup::getPublicKey 获取公钥回调函数
 * @param reply 返回的数据
 * @param replyFlag 返回标志，参考HTTPConn::RESP_SUCCESS和HTTPConn::RESP_FAILED
 * @param pObject
 */
void Signup::getPublicKey(QString reply, int replyFlag, void *pObject) {
  Signup *pthis = (Signup *)pObject;
  if (replyFlag == HTTPConn::HttpResponseStatus::HTTPStatusOK) {
    pthis->doGetPublicKey(reply, replyFlag);
  } else {
    pthis->doGetPublicKey("", replyFlag);
  }
}

/**
 * @brief Signup::registe 注册事务回调函数
 * @param reply 返回的数据
 * @param replyFlag 返回标志，参考HTTPConn::RESP_SUCCESS和HTTPConn::RESP_FAILED
 * @param pObject
 */
void Signup::registe(QString reply, int replyFlag, void *pObject) {
  Signup *pthis = (Signup *)pObject;
  pthis->doGetRegiste(reply, replyFlag);
}

/**
 * @brief Signup::doGetPublicKey 公钥获取后的数据处理
 * @param strReply 网络请求返回的数据
 */
void Signup::doGetPublicKey(QString strReply, int replyFlag) {
  const char *test = "网络异常,网络或服务器异常，请稍后再试.";
  switch (replyFlag) {
    case HTTPConn::HttpResponseStatus::HTTPStatusOK: {
      this->strPK = strReply;
    } break;
    case HTTPConn::RESP_FAILED: {
      QMessageBox::information(this, "网络异常", test);
    } break;
    default: {
      QMessageBox::information(this, "服务器错误", strReply);
    }
  }
  //  std::cout<<strReply<<endl;

  // std::cout << "=========测试rsa加密============" << endl;
  // QByteArray *b = new QByteArray(test);
  // Encrypt::getRSAEncrypt(*b,strReply);
}

/**
 * @brief Signup::doGetRegiste 提交注册信息后处理服务器响应
 * @param strReply 服务器响应返回数据
 * @param replyFlag 服务器处理返回状态
 */
void Signup::doGetRegiste(QString strReply, int replyFlag) {
  switch (replyFlag) {
    case HTTPConn::HttpResponseStatus::HTTPStatusOK: {
      QMessageBox::information(this, "注册成功", strReply);
      (new Signin())->show();
      this->close();
    } break;

    default: {
      QMessageBox::information(this, "注册失败", strReply);
    }
  }
  // std::cout << strReply << endl;
}

void Signup::on_pbOk_clicked() {
  /**
   * {"username": "yhait",
   * "password": "123456",
   * "instruction": "111111111111111111111111",
   * "telephone": "17775739032",
   * "email": "yaozijian@foxmail.com"}
   */
  QString str = this->checkInput();

  if ("" != str) {
    QMessageBox::information(this, "数据输入问题", str);
    return;
  }

  QMap<std::string, QVariant> s;
  Encrypt en;
  std::string strRandKey;
  en.generateRSAKey();
  strRandKey = en.getRandKey();

  this->hc->registCallBack(registe, this);

  // 数据编码
  QString c, p;  //保存注册信息和用户密钥
  QByteArray *bc, *bp;
  QString strTmp;
  {
    s.insert("username", ui->leUsername->text());
    std::string tmp = ui->lePasswd->text().toLocal8Bit().toStdString();
    s.insert("password", en.getMD5(&tmp, (unsigned int)tmp.size()).data());
    s.insert("telephone", ui->lePhoneNumber->text());
    s.insert("email", ui->leEmail->text());
    s.insert("instruction", ui->teDesc->toHtml());
    // bc = en.getAESEncrypt(
    //*(new QByteArray(Data::format(&s, Data::JSON).data())), strRandKey, 0);
    // bp = en.getRSAEncrypt(strRandKey.data());

    c = QString::fromLocal8Bit((*bc).toBase64());
    p = QString::fromLocal8Bit((*bp).toBase64());
  }

  // this->hc->connect();

  // Post http://serverip/regist?c=加密后的注册信息&p=加密后的密钥
  // QMessageBox::information(this, "", Data::format(&s, Data::JSON));
  // QMessageBox::information(this,"公钥：",this->strPK);

  // this->hc->setURL("http://47.88.231.69/regist?c=" +
  //                 Data::format(&s, Data::JSON) + "&p=sdlkfjladskf");
  //  this->hc->setURL("http://47.88.231.69/regist");
  //    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
  //    request.setRawHeader("Accept","text/html, application/xhtml+xml, */*");
  //    request.setRawHeader("Referer","http://localhost:8888/login");
  //    request.setRawHeader("Accept-Language","zh-CN");
  //    request.setRawHeader("X-Requested-With","XMLHttpRequest");
  //    request.setRawHeader("User-Agent","Mozilla/5.0 (compatible; MSIE 9.0;
  //    Windows NT 6.1; WOW64; Trident/5.0)");
  //    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
  //    request.setRawHeader("Accept-Encoding","gzip,deflate");
  //    request.setRawHeader("Host","localhost:8888");
  //    request.setRawHeader("Content-Length","18");
  //    request.setRawHeader("Connection","Keep-Alive");
  //    request.setRawHeader("Cache-Control","no-cache");

  // QByteArray postData;
  // postData.append("myname=lk&mypwd=33");

  strTmp = "http://47.88.231.69/regist?c=" + c + "&p=" + p;
  std::cout << "==========regist url============" << endl
            << strTmp.toStdString() << endl;
  this->hc->setURL(strTmp);
  this->hc->post(c);
}

/**
 * @brief Signup::checkInput 检查界面输入信息是否合法有效
 * @return 如果数据合法有效，则返回空字符串，否则返回错误信息
 */
QString Signup::checkInput() {
  QString s = "";
  if ((ui->leUsername->text().length()) <= 0) s = "请输入你要注册的用户名称。";
  if (ui->lePasswd->text().length() <= 0 ||
      ui->lePasswdRe->text().length() <= 0)
    s = "密码及验证不能为空。";
  if (ui->lePasswd->text() != ui->lePasswdRe->text())
    s = "两次密码不匹配，请重新输入。";
  if (ui->leEmail->text().length() <= 0) s = "请输入你的邮箱地址。";
  if (ui->lePhoneNumber->text().length() <= 0) s = "请输入你的电话号码";
  if (ui->teDesc->toPlainText().length() > 100)
    s = "描述信息限制在100个字符以下。";

  return s;
}

void Signup::on_pbCancel_clicked() { this->close(); }

void Signup::on_teDesc_textChanged() {
  int i = ui->teDesc->toPlainText().length();

  ui->lbDescLength->setText(QString::number(i, 10) + "/100");
}

void Signup::on_pbSelPic_clicked() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("open file"), " ",
      tr("Allfile(*.*);;png file(*.png);;jpg file(*.jpg);;jpeg file(*.jpeg)"));
}
