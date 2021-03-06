#include "MessageForm.h"

#include "newfriend.h"
#include "person.h"
#include "ui_messageform.h"

MessageForm::MessageForm(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MessageForm) {
  ui->setupUi(this);
  this->myFormat = new QTextFrameFormat();
  this->osFormat = new QTextFrameFormat();
  this->setMsgStyle();
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
  this->setWindowModality(Qt::NonModal);

  this->teMessage = new IMTextEdit();
  this->teMessage->setParent(this);
  this->teMessage->setGeometry(220, 420, 411, 141);
  this->teMessage->setDisabled(false);
  this->teMessage->setHidden(false);
  this->teMessage->setReadOnly(false);
  this->teMessage->setAutoFormatting(QTextEdit::AutoAll);

  /////////////
  /***
  this->setMsgStyle();
  QTextCursor cur = ui->tbList->textCursor();
  cur.insertText("A company\n");
  cur.insertBlock();
  cur.insertText("321 City Street");
  cur.insertFrame(fFormat);
  cur.insertText("Industry Park\n try new line.");
  cur.insertBlock();
  cur.insertText("Another country");
  //遍历frame
  for(auto block = rFrame->begin();!block.atEnd();++block) {
      if(block.currentBlock().isValid()) {
          std::cout<<block.currentBlock().text();
      }
      else if(block.currentFrame()) {//frame嵌套，范例只有两层所以不递归了
          auto child_frame = block.currentFrame();
          for(auto block2 = child_frame->begin();!block2.atEnd();++block2) {
              if(block.currentBlock().isValid()) {
                  std::cout<<block2.currentBlock().text();
              }
          }
      }
  }
  */
  //还可以通过root_frame->childFrames()直接获取所字frame
  //遍历文本块
  QTextBlock block = ui->tbList->document()->firstBlock();
  for (int i = 0; i < ui->tbList->document()->blockCount(); i++) {
    /* std::cout << QString(
                     "block num:%1\t block first line number:%2\tblock "
                     "length:%3\t text:")
                     .arg(i)
                     .arg(block.firstLineNumber())
                     .arg(block.length())
              << block.text();
 */
    block = block.next();
  }

  // QTextBlock insert_block = doc->lastBlock().next();
  //在第二行末尾添加
  // cur.setPosition(insert_block.position()+insert_block.length()-1);
  // cur.insertText("change cursor postion and insert");

  /***
  //在第三行开头添加-也就是新frame里面最开始添加
  //方法一，第二行末尾+1就是第三行开头
  cur.setPosition(insert_block.position()+insert_block.length());
  //方法二，position默认返回的就是一个块开头
  cur.setPosition(insert_block.next().position());
  //方法三,利用frame，frame是在一个锚点定位，开头在第二行末尾所以必须加一
  cur.setPosition(fFormat.position()+1);
  cur.insertText("change cursor postion and insert");
*/

  this->tc = new TCPConn();
  this->msgHandle = new MSGHandle();
}

MessageForm::~MessageForm() {
  delete ui;
  delete this->tc;
}

void MessageForm::registCallBack() {
  this->tc->registCallback(MSGHandle::newArrivalFromNW, this->msgHandle);
  this->msgHandle->registCallbackPFUNC_NewSendToUI(newArrival, this);
}

void MessageForm::newArrival(unsigned int is_group_msg, unsigned int from_user,
                             unsigned int to_user, std::string msg_content,
                             void *pObject) {
  // TODO 新到达消息展现处理
  return;
}
/**
 * @brief MessageForm::setMsgStyle
 * @return
 * @desc 设置消息的显示风格，参数从配置中读取。
 */
bool MessageForm::setMsgStyle() {
  try {
    QTextDocument *doc = ui->tbList->document();
    QTextFrame *rFrame = doc->rootFrame();
    QTextFrameFormat rfFormate = rFrame->frameFormat();  //创建框架格式
    doc->setMaximumBlockCount(100);       //设置最多显示最近100行
    rfFormate.setBorderBrush(Qt::white);  //设置边界颜色
    rfFormate.setBorder(1);               //设置边界宽度
    rfFormate.setPosition(QTextFrameFormat::FloatLeft);
    rFrame->setFrameFormat(rfFormate);  //给框架使用格式
    QTextFrameFormat fFormat;
    fFormat.setBackground(Qt::white);  //设置背景色
    fFormat.setMargin(10);             //设置边距
    fFormat.setPadding(5);             //设置填充
    fFormat.setBorder(0);              //设置边界宽度
    fFormat.setBorderStyle(QTextFrameFormat::BorderStyle_Solid);  //设置边框样式
    fFormat.setPosition(QTextFrameFormat::FloatRight);            //右侧
    fFormat.setWidth(
        QTextLength(QTextLength::PercentageLength, 40));  //宽度设置
    fFormat.setForeground(Qt::red);

    this->myFormat->setBackground(Qt::white);  //设置背景色
    this->myFormat->setMargin(10);             //设置边距
    this->myFormat->setPadding(5);             //设置填充
    this->myFormat->setBorder(0);              //设置边界宽度
    this->myFormat->setBorderStyle(
        QTextFrameFormat::BorderStyle_Solid);  //设置边框样式
    this->myFormat->setPosition(QTextFrameFormat::FloatRight);  //右侧
    this->myFormat->setWidth(
        QTextLength(QTextLength::PercentageLength, 80));  //宽度设置
    this->myFormat->setForeground(Qt::darkYellow);

  } catch (...) {
  }
  return true;
}

void MessageForm::on_btnSendMsg_clicked() {
  std::string strMsg;
  Person *p = new Person;

  p->setID("hhww");
  strMsg = p->getID() + ":\n" + this->teMessage->toHtml().toStdString();
  QTextDocument *myMsg = this->teMessage->document();

  // std::cout << this->teMessage->toHtml() << endl;
  QTextDocument *doc = ui->tbList->document();
  QTextBlock insert_block = doc->lastBlock().next();
  QTextCursor cur = ui->tbList->textCursor();

  cur.insertFrame(*this->myFormat);
  // cur.setPosition(insert_block.position()+insert_block.length()-1);
  cur.insertBlock();
  cur.setPosition(doc->lastBlock().position() + insert_block.length() - 1);
  cur.insertHtml(QString::fromStdString(strMsg));
  cur.insertHtml("<br>");
  // cur.in

  // 网络发送
  this->msgHandle->sendMessage(0, 0, 0, strMsg);
}

void MessageForm::stringToHtmlFilter(QString &str) {
  //注意这几行代码的顺序不能乱，否则会造成多次替换
  str.replace("&", "&amp;");
  str.replace(">", "&gt;");
  str.replace("<", "&lt;");
  str.replace("\"", "&quot;");
  str.replace("\'", "&#39;");
  str.replace(" ", "&nbsp;");
  str.replace("\n", "<br>");
  str.replace("\r", "<br>");
}

void MessageForm::on_btnAddFriend_clicked() {
  NewFriend *mw = new NewFriend;
  //  mw->setModal(true);
  //  mw->setParent(this);
  mw->show();
  // QMessageBox::information(nullptr,"new","new friend added.");
  // this->close();
}
