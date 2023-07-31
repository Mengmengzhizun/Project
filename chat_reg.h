#ifndef CHAT_REG_H
#define CHAT_REG_H
#include <QWidget>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>

namespace Ui {
class chat_Reg;
}

class chat_Reg : public QWidget
{
    Q_OBJECT

public:
    explicit chat_Reg(QSqlDatabase *db,QWidget *parent = nullptr);//传入数据库指针对数据库操作
    ~chat_Reg();

public slots:
    void user_register();

private:
    Ui::chat_Reg *ui;
    QSqlDatabase *reg_db; //继承用
};

#endif // CHAT_REG_H
