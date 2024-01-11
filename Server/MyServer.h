
#ifndef MYSERVER_H
#define MYSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QTextEdit>
#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

class QTcpServer;
class QTextEdit;
class QTcpSocket;

class MyServer : public QWidget {
    Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    QTextEdit*  m_ptxt;
    quint16     m_nNextBlockSize;
    QString login;

private:
    void sendTablesUser(QTcpSocket* pSocket);
    void sendTablesAdmin(QTcpSocket* pSocket);

    void sendToClient(QTcpSocket* pSocket, const QString& str);

    void sendToClientInfo(QTcpSocket* pSocket);

    void sendToClientGroups(QTcpSocket* pSocket);
    void sendToClientWork(QTcpSocket* pSocket);
    void sendToClientSquads(QTcpSocket* pSocket);

    void sendToClientSEL(QTcpSocket* pSocket, QString table_name);
    void sendToClientSELChanging(QTcpSocket* pSocket, QString table);
    void sendToClientSELFilter(QTcpSocket* pSocket, QString table, int id);
    void sendToClientSELFindStudent(QTcpSocket* pSocket, QString lastname, QString name, QString middlename);
    void sendToClientSELGroupBy(QTcpSocket* pSocket, QString sign, QString filter);
    void sendToClientSELGroupCount(QTcpSocket* pSocket);

    void sendToCLientSELStudSquad(QTcpSocket* pSocket);
    void sendToCLientSELStudAddress(QTcpSocket* pSocket);
    void sendToCLientSELStudGroups(QTcpSocket* pSocket);

    void sendToClientAVGADdress(QTcpSocket* pSocket);
    void sendToClientAVGSalary(QTcpSocket* pSocket);
    void sendToClientMAX(QTcpSocket* pSocket);
    void sendToClientNorm(QTcpSocket* pSocket);

    void sendInsertToDBStudents(QTcpSocket* pSocket, QString lastname, QString name, QString middlename, QString curs, int id_group, int id_squad, int id_place, QString amount_of_work, float salary);
    void sendInsertToDBWorkPlace(QTcpSocket* pSocket, QString type_of_construction, QString address);
    void sendInsertToDBGroups(QTcpSocket* pSocket, QString newGroup);
    void sendInsertToDBSquads(QTcpSocket* pSocket, QString newSquad);

    void sendUpdateToDBSalary(QTcpSocket* pSocket, int id_student, int number);

    void sendUpdateToDB(QTcpSocket* pSocket, QString table_name, QString col_name_table, QString col_name, QString change, int id);

    void sendDeleteToDB(QString table_name, QString col_name, int id);

public:
    MyServer(int nPort, QWidget* pwgt = 0);
    QJsonDocument doc;
    QJsonParseError docError;

public slots:
    virtual void slotNewConnection();
    void slotReadClient   ();
};

#endif // MYSERVER_H
