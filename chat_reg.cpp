#include "chat_reg.h"
#include "ui_chat_reg.h"


//注册功能

chat_Reg::chat_Reg(QSqlDatabase *db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chat_Reg)
{
    ui->setupUi(this);

    //连接数据库
    reg_db=db;
    connect(ui->pushButton,&QPushButton::clicked,this,&chat_Reg::user_register);

}

void chat_Reg::user_register()
{
    QString account=ui->reg_line_f->text();
    QString pwd=ui->reg_line_s->text();
    QSqlQuery query;
    QSqlError temp_error;



    //进行注册，将信息存储于数据库
    QString sql=QString("select * from user where id=%1;").arg(account);
    bool success = query.exec(sql);
    if(query.next()==true)
    {
        QMessageBox::information(this,"tips","该账号已注册");
    }
    else
    {//注册
        QString sql=QString("INSERT user VALUES(%1,%2)").arg(account).arg(pwd);
        success = query.exec(sql);
        QMessageBox::information(this,"tips","注册成功");
        //qDebug()<<success;
    }





}

chat_Reg::~chat_Reg()
{
    delete ui;
}
