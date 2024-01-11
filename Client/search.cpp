#include "search.h"
#include "ui_search.h"
#include <QMessageBox>

search::search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::search)
{
    ui->setupUi(this);
}

void search::TcpSocket(QTcpSocket *socket)
{
    foreignSocket = socket;
}

search::~search()
{
    delete ui;
}

void search::on_pushButton_clicked()
{
    QByteArray  arrBlock;
    int num = 10;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    QRegularExpression russianAlphabet("^[А-Яа-я]+$");


    QString lastname = ui->lineEdit->text();
    QString name = ui->lineEdit_2->text();
    QString middlename = ui->lineEdit_3->text();

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");

    if (russianAlphabet.match(lastname).hasMatch() && russianAlphabet.match(name).hasMatch() && russianAlphabet.match(middlename).hasMatch())
    {
        out << quint16(0) << num << lastname << name << middlename;
        out.device()->seek(0);
        //qDebug() << arrBlock.size();
        out << quint16(arrBlock.size() - sizeof(quint16));
        //qDebug() << arrBlock;

        foreignSocket->write(arrBlock);
    }
    else
    {
        QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");
        return;
    }
}

