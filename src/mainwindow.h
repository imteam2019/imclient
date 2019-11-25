#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>
#include <QTextFrame>
#include <QTextBlock>
#include <QDebug>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSendMsg_clicked();

    void on_btnAddFriend_clicked();

private:
    Ui::MainWindow *ui;
    QTextFrameFormat *myFormat;
    QTextFrameFormat *osFormat;
    bool setMsgStyle();
    void stringToHtmlFilter(QString &str);
    void stringToHtml(QString &str,QColor crl);
};
#endif // MAINWINDOW_H
