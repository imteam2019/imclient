#ifndef IMTEXTEDIT_H
#define IMTEXTEDIT_H

#include <QObject>
#include <QWidget>
#include <QTextEdit>
#include <QMimeData>
#include <QFileInfo>
#include <QImageReader>
#include <QtDebug>

class IMTextEdit : public QTextEdit
{
public:
    IMTextEdit();
    bool canInsertFromMimeData(const QMimeData* source) const;
    void insertFromMimeData(const QMimeData* source);

private:
    void dropImage(const QUrl& url, const QImage& image);
    void dropTextFile(const QUrl& url);
};
#endif // IMTEXTEDIT_H
