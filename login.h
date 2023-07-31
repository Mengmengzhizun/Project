#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>


namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots://槽函数
    void button_clicked_event();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();



private:
    Ui::login *ui;
    std::string user_id;
    std::string user_passwd;
    QSqlDatabase db;
    unsigned int port=0;
};

#endif // LOGIN_H
