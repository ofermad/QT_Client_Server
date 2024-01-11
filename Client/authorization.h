#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class authorization;
}

class authorization : public QWidget
{
    Q_OBJECT

public:
    explicit authorization(QWidget *parent = nullptr);
    ~authorization();
    void TcpSocket(QTcpSocket *socket);
    QTcpSocket* foreignSocket;
    void Login();
    Ui::authorization *ui;

signals:
    void textValid(QString login, QString password);

private slots:

    void on_pushButton_clicked();

private:
    QString login;
    QString password;
    //Ui::authorization *ui;
};

#endif // AUTHORIZATION_H
