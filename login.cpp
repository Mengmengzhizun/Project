#include "login.h"
#include "ui_login.h"
#include "chat_reg.h"
#include "widget.h"
login::login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    //初始化数据库
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("login_databases");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("qweasd221");

    if(db.open())
    {
        QMessageBox::information(this,"信息","连接数据库成功");
    }
    else
    {
        QMessageBox::information(this,"信息","连接数据库失败");
    }

     //登录event
    connect(ui->login_button,&QPushButton::clicked,this,&login::button_clicked_event);
}

login::~login()
{
    delete ui;
}

void login::button_clicked_event()
{

    //登录功能
    QString id=ui->id_LineEdit->text();
    QString pwd=ui->pwd_LineEdit->text();
    if(id=="")
    {
        QMessageBox::information(this,"tips","请输入账号");
    }
    else if(id!=""&&pwd=="")
    {
        QMessageBox::information(this,"tips","请输入密码");
    }


    //验证账号是否存在
    QSqlQuery query;
    QString sql=QString("select * from user where id=%1;").arg(id);
    bool success = query.exec(sql);


    //验证端口是否设置
    if(port==0)
    {
        success =0;
        QMessageBox::information(this,"tips","请设置端口");
    }


    //正确设置后，验证账号密码是否正确
    if (!success) {
        QSqlError error = query.lastError();
        if (error.type() != QSqlError::NoError) {

                // 其他错误
                qDebug() << "错误" << error.text();
            }}
    else {
        if (query.next()) {
            QString temp_pwd=query.value(1).toString();

            if(ui->pwd_LineEdit->text()==temp_pwd)
            {
                QMessageBox::information(this,"tips","登录成功");
                this->hide();
                Widget *main_window=new Widget(id,port);


                main_window->show();
            }
            else
            {
                QMessageBox::information(this,"tips","密码错误");
            }
        } else {
            QMessageBox::information(this,"tips","请注册账号");
        }
    }
}



//转入主界面
void login::on_pushButton_clicked()
{

    if(db.open())
    {
    chat_Reg *reg_window=new chat_Reg(&db);
        reg_window->show();}
    else
    {
        QMessageBox::information(this,"tips","请连接数据库");
    }
}


//设置端口
void login::on_pushButton_2_clicked()
{
    port=ui->port_line->text().toUInt();
    QMessageBox::information(this,"tips","设置成功");
}

