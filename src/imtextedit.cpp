#include "imtextedit.h"

IMTextEdit::IMTextEdit(QWidget *parrent) {}

bool IMTextEdit::canInsertFromMimeData(const QMimeData* source) const {
  return source->hasImage() || source->hasUrls() ||
         QTextEdit::canInsertFromMimeData(source);
}

void IMTextEdit::insertFromMimeData(const QMimeData* source) {
  QStringList sl = source->formats();
  QByteArray data;
  // qDebug() << source->html() << endl;
  for (int i = 0; i < sl.size(); ++i) {
    data.append(source->data(sl[i]));
  }
  std::string* s = new std::string(data.data(), data.length());
  std::cout << endl << s->length() << ":" << data.length() << endl;
  if (source->hasImage()) {
    static int i = 1;
#ifdef MY_DEBUG_ON
    // std::cout << source->urls().at(0).toString().toStdString() << endl;
    // std::cout << source->html().toStdString() << endl;
#endif
    //针对图片进行base64编码
    /*
    QImage image = qvariant_cast<QImage>(source->imageData());
    QByteArray array;
    QBuffer buffer(&array);
    image.save(&buffer, "png", 1);

    qDebug() << "image size:Compress -1 size:\t" << image.sizeInBytes() << ":"
             << array.size() << endl;
    buffer.close();


    QByteArray base64Array = array.toBase64();
    QByteArray comImageArray =
        "<img src=data:image/png;base64," + base64Array + "/>";

    textCursor().insertHtml(QString(comImageArray));
    */
    dropImage(QUrl(), qvariant_cast<QImage>(source->imageData()));

  } else if (source->hasUrls()) {
    foreach (QUrl url, source->urls()) {
      QFileInfo info(url.toLocalFile());
      if (QImageReader::supportedImageFormats().contains(
              info.suffix().toLower().toLatin1()))
        dropImage(url, QImage(info.filePath()));
      else
        dropTextFile(url);
    }
  } else {
    QTextEdit::insertFromMimeData(source);
  }

  // qDebug() << this->toHtml() << endl;
}

void IMTextEdit::dropImage(const QUrl& url, const QImage& image) {
  if (!image.isNull()) {
    // 压缩图片
    Compress* c = new CompressJpeg();
    unsigned long outDataLen = 0;
    unsigned long* outSize = &outDataLen;
    unsigned char* outbuf;
    outbuf = c->compress(image.bits(), image.width() * image.height(),
                         image.width(), image.height(), outSize);
    if (outbuf == nullptr) {
      printf("Jpeg comress error.\n");
      return;
    }
    QImage qi = QImage::fromData(outbuf, outDataLen, "jpg");
    // QImage qi = image;
    //针对图片进行html处理

    QByteArray array;
    QBuffer buffer(&array);
    // image.save(&buffer, "png", 1);
    image.save("/Users/anthony.shengbo.zeng/Desktop/image.jpg", "jpg", 100);
    qi.save("/Users/anthony.shengbo.zeng/Desktop/qi.jpg", "jpg", 75);
    qi.save(&buffer, "jpg", 100);
    QImage qa = QImage::fromData(array, "jpg");
    qa.save("/Users/anthony.shengbo.zeng/Desktop/qa.png", "jpg", 75);

    qDebug() << "image size:Compress -1 size:\t" << image.sizeInBytes() << ":"
             << qi.sizeInBytes() << ":" << array.size() << ":" << outDataLen
             << endl;
    qDebug() << "libjpeg compress radio:\t"
             << qi.sizeInBytes() / image.sizeInBytes() * 100 << "%" << endl;
    qDebug() << "QImage compress radio:\t"
             << array.size() / qi.sizeInBytes() * 100 << "%" << endl;
    buffer.close();

    /*! 数据转base64 */
    QByteArray base64Array = array.toBase64();
    QByteArray comImageArray =
        "<img src=data:image/jpg;base64," + base64Array + "/>";

    textCursor().insertHtml(QString(comImageArray));
  }
}

void IMTextEdit::dropTextFile(const QUrl& url) {
  QFile file(url.toLocalFile());
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    textCursor().insertText(file.readAll());
}
