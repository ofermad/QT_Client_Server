#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class search;
}

class search : public QWidget
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();

    void TcpSocket(QTcpSocket *socket);
    QTcpSocket* foreignSocket;

    Ui::search *ui;

private slots:
    void on_pushButton_clicked();

private:
    //Ui::search *ui;
};

#endif // SEARCH_H
