#ifndef ADDING_H
#define ADDING_H

#include <QWidget>
#include <QStandardItem>
#include <QTcpSocket>

namespace Ui {
class adding;
}

class adding : public QWidget
{
    Q_OBJECT

public:
    explicit adding(QWidget *parent = nullptr);
    ~adding();
    void showTable(QStandardItemModel *model);
    void TcpSocket(QTcpSocket *socket);
    QTcpSocket* foreignSocket;
    //bool onlyRussianLetters(QString text);
    QMap<QString, int> foreignMapAddingGroups;
    QMap<QString, int> foreignMapAddingSquads;
    QMap<QString, int> foreignMapAddingWork;
    Ui::adding *ui;

private:
    bool onlyRussianLettersAdding(QString text);

private slots:
    void on_pushButton_clicked();

    void on_comboBox_2_currentIndexChanged(int index);
};

#endif // ADDING_H
