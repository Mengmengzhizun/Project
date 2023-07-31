#include "widget.h"
#include "ui_widget.h"
#include<iostream>


Widget::Widget(QString account,unsigned p,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket=new QTcpSocket;
    ID=account;
    port=p;
    socket->connectToHost(QHostAddress::LocalHost,port);//TCP连接

    if(!socket->isOpen())
    {
        QMessageBox::information(this,"tips","连接服务器失败");
    }

    //这个是聊天框回车输出
    connect(ui->lineEdit, &QLineEdit::returnPressed, ui->pushButton, &QPushButton::click);

    //回收服务器信息并插入到主界面TEXT框
    ser_reciver *r=new ser_reciver(socket);
    r->start();
    connect(r,&ser_reciver::ser_rec,this, &Widget::data_enter);
    //QMessageBox::information(this,"tips","test1");

    connect(&timer, &QTimer::timeout,this,[=](){updata_msg(ui->textEdit);});

}

Widget::~Widget()
{
    delete ui;
}

void Widget::data_enter(QByteArray ba)
{

    //QMessageBox::information(this,"tips","test2");

    //处理服务器传入的数据
    if (ba.startsWith("Image:"))
    {
        //QMessageBox::information(this,"tips","recive photos");
        QByteArray imageData = ba.mid(6);


        QImage image;
        image.loadFromData(imageData);
        QSize thumbnailSize(100, 100);
        QImage thumbnail = image.scaled(thumbnailSize, Qt::KeepAspectRatio);


        QPixmap pixmap = QPixmap::fromImage(thumbnail);
        QTextCursor cursor(ui->textEdit->textCursor());
        cursor.movePosition(QTextCursor::End);

        // 将图像插入到 QTextEdit
        cursor.insertImage(pixmap.toImage());
        cursor.movePosition(QTextCursor::NextBlock);

    }
else
    {QString in_text=QString(ba);


    //设置左居中
    QTextCursor cursor = ui->textEdit->textCursor();
    ui->textEdit->setAlignment(Qt::AlignLeft);
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    //插入数据
    cursor.insertText(QString(in_text));


    //输入框清空
    ui->lineEdit->setText("");}
}


void Widget::on_pushButton_clicked()
{
    //发送聊天信息
    QString new_message=QString("%1:%2\n").arg(ID).arg(ui->lineEdit->text());
    QByteArray ba=new_message.toUtf8();
    socket->write(ba);


    if(socket->state()!=QAbstractSocket::ConnectedState)
    {
        QMessageBox::information(this,"tips","wrong");
    }


}




//重新连接
void Widget::on_pushButton_2_clicked()
{
    socket->connectToHost(QHostAddress::LocalHost,port);
    if(socket->isOpen())
    {
        QMessageBox::information(this,"tips","重新连接服务器成功");
    }
    else
    {
        QMessageBox::information(this,"tips","重新连接服务器失败");
    }

}


void Widget::on_pushButton_3_clicked()
{
    socket->disconnectFromHost();
    QMessageBox::information(this,"tips","注销成功");
    this->close();
}




void Widget::on_pushButton_4_clicked()
{
    timer.setInterval(ui->lineEdit_2->text().toInt()*1000); // 秒为单位
    timer.start();
}

void Widget::updata_msg(QTextEdit* msg_text)
{

    // 获取当前文本内容
    QString text = msg_text->toPlainText();

    // 查找第一行的终止位置
    int newlinePos = text.indexOf('\n');

    // 如果存在第一行，则删除第一行内容
    if (newlinePos != -1) {
        text.remove(0, newlinePos + 1); // +1 是为了删除换行符
    }

    // 设置更新后的文本内容
    msg_text->setPlainText(text);
}


void Widget::on_pushButton_5_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "选择图片", "", "Images (*.png *.jpg *.jpeg)");
    QFile file(imagePath);

    if (!imagePath.isEmpty()&&file.open(QIODevice::ReadOnly))
    {
        QByteArray message;
        message.append("Image:");
        QByteArray imageData = file.readAll();
        message.append(imageData);

        socket->write(message);
        socket->waitForBytesWritten();
        file.close();
    }
}

