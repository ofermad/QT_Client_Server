#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QFrame>
#include <QWidget>
namespace Ui {
class myclient;
}

class myclient : public QFrame
{
    Q_OBJECT

public:
    explicit myclient(QWidget *parent = nullptr);
    ~myclient();

private slots:
    void on_pushButton_clicked();

private:
    Ui::myclient *ui;
};

#endif // MYCLIENT_H
