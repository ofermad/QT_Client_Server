#include "authorization.h"
#include "mainwindow.h"
#include "ui_authorization.h"
#include <QTcpSocket>
#include <QMessageBox>

authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
}

authorization::~authorization()
{
    delete ui;
}


void authorization::TcpSocket(QTcpSocket *socket)
{
    foreignSocket = socket;
    qDebug() << "\nAUTHO socket: " << foreignSocket;
}

void authorization::Login()
{
    if (login == "" && password == "")
    {
        login = ui->lineEdit->text();
        password = ui->lineEdit_2->text();
    }

    qDebug() << login;
    qDebug() << password;

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");

    if (login == "user" && password == "user")
    {
        emit textValid(login, password);
        this->close();
        return ;
    }
    else if (login == "admin" && password == "admin")
    {
        emit textValid(login, password);
        this->close();
        return ;
    }
    else
    {
        login = "";
        password = "";
        QMessageBox::warning(0, "Отказано в доступе", "Неверный логин или пароль");
        return ;
    }
}

void authorization::on_pushButton_clicked()
{
    Login();
}

