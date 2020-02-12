#ifndef LITTERIEM_H
#define LITTERIEM_H

#include <QDebug>
#include <QMouseEvent>
#include <QWidget>

#include "messageform.h"

namespace Ui {
class LitterIem;
}

class LitterIem : public QWidget {
  Q_OBJECT

 public:
  /**
   * @brief LitterIem
   * @param picPath 头像的文件路径
   * @param parent
   */
  explicit LitterIem(QString picPath, QWidget *parent = nullptr);
  ~LitterIem();

 private:
  Ui::LitterIem *ui;

  // 增加双击信号处理

 signals:
  void doubleClicked();

 public slots:
  void mouseClicked();

 protected:
  void mouseDoubleClickEvent(QMouseEvent *);
  // void mousePressEvent(QMouseEvent *ev);
  // void mouseReleaseEvent(QMouseEvent *ev);

 private:
  QPoint mousePos;
};

#endif  // LITTERIEM_H
