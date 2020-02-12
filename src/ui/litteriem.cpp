#include "litteriem.h"

#include <QPixmap>

#include "ui_litteriem.h"

LitterIem::LitterIem(QString picPath, QWidget *parent)
    : QWidget(parent), ui(new Ui::LitterIem) {
  ui->setupUi(this);
  QPixmap p(picPath);
  ui->label_pic->setPixmap(p);
  ui->lbName->setText(picPath);
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
  this->setWindowModality(Qt::NonModal);

  connect(this, SIGNAL(doubleClicked()), this, SLOT(mouseClicked()));
}

LitterIem::~LitterIem() { delete ui; }

void LitterIem::mouseClicked() {
  //处理代码
  MessageForm *mf = new MessageForm();
  mf->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
  mf->setWindowModality(Qt::NonModal);

  mf->show();

  // mf.setVisible(true);
  // mf->show();
  qDebug() << ui->lbName->text() << endl;
}

void LitterIem::mouseDoubleClickEvent(QMouseEvent *ev) {
  if (ev->button() == Qt::LeftButton) emit doubleClicked();
}

/*
void LitterIem::mousePressEvent(QMouseEvent *ev) {
  this->mousePos = QPoint(ev->x(), ev->y());
}

void LitterIem::mouseReleaseEvent(QMouseEvent *ev) {
  if (this->mousePos == QPoint(ev->x(), ev->y())) emit doubleClicked();
}

*/
