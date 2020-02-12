#ifndef IMTEXTEDIT_H
#define IMTEXTEDIT_H

#include <QBuffer>
#include <QFileInfo>
#include <QImage>
#include <QImageReader>
#include <QMimeData>
#include <QObject>
#include <QTextEdit>
#include <QVariant>
#include <QWidget>
#include <QtDebug>
#include <iostream>

#include "common/encrypt.h"
#include "compress/compress.h"
#include "compress/compressjpeg.h"

using namespace std;
class IMTextEdit : public QTextEdit {
 public:
  IMTextEdit();
  bool canInsertFromMimeData(const QMimeData* source) const;
  void insertFromMimeData(const QMimeData* source);

 private:
  void dropImage(const QUrl& url, const QImage& image);
  void dropTextFile(const QUrl& url);
};
#endif  // IMTEXTEDIT_H
