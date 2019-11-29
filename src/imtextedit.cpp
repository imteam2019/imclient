#include "imtextedit.h"

IMTextEdit::IMTextEdit()
{

}

bool IMTextEdit::canInsertFromMimeData(const QMimeData* source) const
    {
        return source->hasImage() || source->hasUrls() ||
            QTextEdit::canInsertFromMimeData(source);
    }


void IMTextEdit::insertFromMimeData(const QMimeData* source)
{
    QStringList sl=source->formats();
    QByteArray data;

    for(int i=0;i<sl.size();++i){
        data.append(source->data(sl[i]));

    }
    qDebug()<<data<<endl;

    //this->insertHtml(QString::fromLatin1(data));


    if (source->hasImage())
    {
        static int i = 1;
        qDebug()<<source->urls()<<endl;
        qDebug()<<source->html()<<endl;
        QUrl url(QString("dropped_image_%1").arg(i++));

        dropImage(url, qvariant_cast<QImage>(source->imageData()));
    }
    else if (source->hasUrls())
    {
        foreach (QUrl url, source->urls())
        {
            QFileInfo info(url.toLocalFile());
            if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
                dropImage(url, QImage(info.filePath()));
            else
                dropTextFile(url);
        }
    }
    else
    {
        QTextEdit::insertFromMimeData(source);
    }

}


/**d
void IMTextEdit::insertFromMimeData(const QMimeData *source){
    if (source->hasText() && !source->hasFormat("application/vnd.oasis.opendocument.text")) {
        QString context = source->text();
        QByteArray data=source->data();
                QStringList conList = context.split("\n");
                QTextCursor cursor = this->textCursor();

                //int origState = cursor.block()).userState();

                for (int i = 0; i < conList.length(); ++i) {
                    cursor.insertBlock();
                    cursor.insertHtml(conList[i]); //插入文本内容
                    //cursor.block().setUserState(origState);
                }
        } else {
            // 默认行为
            QTextEdit::insertFromMimeData(source);
        }
}
*/

void IMTextEdit::dropImage(const QUrl& url, const QImage& image)
    {
        if (!image.isNull())
        {
            document()->addResource(QTextDocument::ImageResource, url, image);
            textCursor().insertImage(url.toString());
        }
    }

void IMTextEdit::dropTextFile(const QUrl& url)
{
    QFile file(url.toLocalFile());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        textCursor().insertText(file.readAll());
}
