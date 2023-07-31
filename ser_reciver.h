#ifndef SER_RECIVER_H
#define SER_RECIVER_H

#include <QObject>
#include<QTcpSocket>
#include<QThread>


//线程接收

class ser_reciver : public QThread
{
    Q_OBJECT
public:
    explicit ser_reciver(QTcpSocket *s,QObject *parent = nullptr);
    void run();

public slots://槽函数 构建自定义信号
    void server_rec_funtion();

signals://自定义信号
    void ser_rec(QByteArray a);

public:
    QTcpSocket *socket;

};

#endif // SER_RECIVER_H
