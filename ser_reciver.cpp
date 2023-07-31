#include "ser_reciver.h"

ser_reciver::ser_reciver(QTcpSocket *s,QObject *parent)
    : QThread{parent}
{   //初始化对象socket
    socket=s;
}




//自定义信号
void ser_reciver::run()
{
    connect(socket,&QTcpSocket::readyRead,this,&ser_reciver::server_rec_funtion);

}


void ser_reciver::server_rec_funtion()
{

    QByteArray ba=socket->readAll();
    emit ser_rec(ba);

}
