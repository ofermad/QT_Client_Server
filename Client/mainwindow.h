
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "adding.h"
#include "changing.h"
#include "authorization.h"
#include "search.h"
#include <QWidget>
#include <QTcpSocket>
#include <QTableView>
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QJsonDocument doc;
    QJsonParseError docError;
    QTcpSocket* m_pTcpSocket;
    QMap<QString, int> myMapGroups;
    QMap<QString, int> myMapWork;
    QMap<QString, int> myMapSquads;
    void authorizationCheck(QString login, QString password);

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );
    void slotSendToServerSEL();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void closeEvent(QCloseEvent *event) override;

    //void on_checkBox_stateChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

private:
    //QTcpSocket* m_pTcpSocket;
    QTableView* table;
    quint16     m_nNextBlockSize;
    adding*     secondWindow;
    changing*   thirdWindow;
    authorization* loginWindow;
    search*     searchWindow;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
