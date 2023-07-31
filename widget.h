#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QDebug>
#include<QMessageBox>
#include<QByteArray>
#include<ser_reciver.h>
#include<qtimer.h>
#include <QTextEdit>
#include<QFile>
#include<QFileDialog>
#include<QBuffer>




QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QString account,unsigned p,QWidget *parent = nullptr);
    ~Widget();

private slots://槽函数
    void on_pushButton_clicked();
    void data_enter(QByteArray b);
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void updata_msg(QTextEdit* msg_text);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
    QString ID;
    unsigned port;
    QTimer timer;
};
#endif // WIDGET_H
