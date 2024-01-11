#ifndef CHANGING_H
#define CHANGING_H

#include <QWidget>
#include <QTcpSocket>
#include <QStandardItemModel>

namespace Ui {
class changing;
}

class changing : public QWidget
{
    Q_OBJECT

public:
    explicit changing(QWidget *parent = nullptr);
    ~changing();
    void TcpSocket(QTcpSocket *socket);
    QTcpSocket* foreignSocket;
    //bool onlyRussianLetters(QString text);
    Ui::changing *ui;

    QMap<QString, int> foreignMapChangingGroups;
    QMap<QString, int> foreignMapChangingSquads;
    QMap<QString, int> foreignMapChangingWork;

    void recivedModel(QStandardItemModel *model);
    int k = 0;

private:
    bool onlyRussianLettersChanging(QString text);
    QStandardItemModel* recievedmodel;
    QStandardItemModel* tempModel;
    quint16     m_nNextBlockSize;
    void handleDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles);
    int row = 0;
    int column = 0;
    int flag = 1;
    int flag1 = 1;


private slots:
    void on_pushButton_2_clicked();
    //void sendToServerInsert();
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_2_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
};

#endif // CHANGING_H
