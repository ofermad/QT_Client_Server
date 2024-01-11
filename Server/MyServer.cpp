#include "MyServer.h"
#include "DatabaseConn.h"
#include <QtGui>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableView>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QString>
#include <QSqlRecord>
#include <QSqlError>

MyServer::MyServer(int nPort, QWidget* pwgt /*=0*/) : QWidget(pwgt)
    , m_nNextBlockSize(0)
{
    m_ptcpServer = new QTcpServer(this);

    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        QMessageBox::critical(0,
                              "Server Error",
                              "Unable to start the server:"
                                  + m_ptcpServer->errorString()
                              );
        m_ptcpServer->close();
        return;
    }

    connect(m_ptcpServer, SIGNAL(newConnection()),
            this,         SLOT(slotNewConnection())
            );

    m_ptxt = new QTextEdit;
    m_ptxt->setReadOnly(true);

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Server</H1>"));
    pvbxLayout->addWidget(m_ptxt);
    setLayout(pvbxLayout);
}

/*virtual*/ void MyServer::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();

    connect(pClientSocket, SIGNAL(disconnected()),
            pClientSocket, SLOT(deleteLater())
            );
    connect(pClientSocket, SIGNAL(readyRead()),
            this,          SLOT(slotReadClient())
            );

    //sendToClient(pClientSocket, "Server Response: Connected!");
}

void MyServer::sendTablesUser(QTcpSocket* pSocket)
{
    qDebug() << "\nUser pSocket: " << pSocket;

    int num = 5;
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT tablename FROM pg_catalog.pg_tables WHERE schemaname != 'pg_catalog' AND schemaname != 'information_schema' ORDER BY tablename DESC;");

    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out << model->rowCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        out << model->data(model->index(row, 0), Qt::DisplayRole).toString();
        //qDebug() << model->data(model->index(row, 0), Qt::DisplayRole).toString();
    }

    qDebug() << "\nGroups pSocket: " << pSocket;
    out.setVersion(QDataStream::Qt_6_4);

    model->setQuery("SELECT id_group, group_name FROM stud_groups;");

    //out << quint16(0) << num;
    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    model->setQuery("SELECT id_squad, construction_team FROM squads;");

    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    model->setQuery("SELECT id_place, address FROM work_place;");

    out << model->rowCount() << model->columnCount();
    qDebug() << "Work rows and col: " << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << "\nArray block of groups: " << arrBlock;

    pSocket->write(arrBlock);

    QSqlQuery query;
    QString str = QString("SET ROLE \"user\";");
    qDebug() << str;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
}

void MyServer::sendTablesAdmin(QTcpSocket* pSocket)
{
    qDebug() << "\nAdmin pSocket: " << pSocket;

    int num = 5;
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT tablename FROM pg_catalog.pg_tables WHERE schemaname != 'pg_catalog' AND schemaname != 'information_schema' ORDER BY tablename DESC;");

    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out << model->rowCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        out << model->data(model->index(row, 0), Qt::DisplayRole).toString();
        //qDebug() << model->data(model->index(row, 0), Qt::DisplayRole).toString();
    }

    //out1.device()->seek(0);
    //out1 << quint16(block.size() - sizeof(quint16));

    //pSocket->write(block);

    qDebug() << "\nGroups pSocket: " << pSocket;
    //QByteArray  arrBlock;
    //QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    //int num = 0;

    //QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id_group, group_name FROM stud_groups;");

    //out << quint16(0) << num;
    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    model->setQuery("SELECT id_squad, construction_team FROM squads;");

    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    model->setQuery("SELECT id_place, address FROM work_place;");

    out << model->rowCount() << model->columnCount();
    qDebug() << "Work rows and col: " << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << "\nArray block of groups: " << arrBlock;

    pSocket->write(arrBlock);

    QSqlQuery query;
    QString str = QString("SET ROLE \"admin\";");
    qDebug() << str;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }

    //sendToClientInfo(pSocket);
}

void MyServer::sendToClientInfo(QTcpSocket* pSocket)
{
    qDebug() << "\nGroups pSocket: " << pSocket;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int num = 100;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id_group, group_name FROM stud_groups;");

    out << quint16(0) << num;
    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    model->setQuery("SELECT * FROM squads;");

    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    model->setQuery("SELECT id_place, address FROM work_place;");

    out << model->rowCount() << model->columnCount();
    qDebug() << "Work rows and col: " << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << "\nArray block of groups: " << arrBlock;

    pSocket->write(arrBlock);
}

void MyServer::sendToClientGroups(QTcpSocket* pSocket)
{
    qDebug() << "\nGroups pSocket: " << pSocket;
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int num = 10;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id_group, group_name FROM stud_groups;");

    out << quint16(0) << num;
    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << "\nArray block of groups: " << arrBlock;

    pSocket->write(arrBlock);
}

void MyServer::sendToClientWork(QTcpSocket* pSocket)
{
    qDebug() << "\nWork pSocket: " << pSocket;

    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int num = 8;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id_place, address FROM work_place;");

    out << quint16(0) << num;
    out << model->rowCount() << model->columnCount();
    qDebug() << "Work rows and col: " << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << "\nArray block of work: " << arrBlock;

    pSocket->write(arrBlock);
}

void MyServer::sendToClientSquads(QTcpSocket* pSocket)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int num = 9;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id_squad, construction_team FROM squads;");

    out << quint16(0) << num;
    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << "\nArray block of squads: " << arrBlock;

    pSocket->write(arrBlock);
}

void MyServer::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();

    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_6_4);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            m_nNextBlockSize = 0;
            break;
        }


        QByteArray Data;
        QString lastname, name, middlename, change, col_name, table_name, password, table, amount_of_work, newSquad, newGroup, type_of_construction, address , col_name_table, id_groupstr,id_addressstr, id_squadstr;
        int num = 0, id_group = 0, id_squad = 0, id_place = 0, id = NULL;
        float salary = NULL;
        in >> num;
        QString s = QString::number(num);
        //qDebug() << s << lastname << name << middlename << id_group;
        qDebug() << "\nnum sended: " << num;


        QString strMessage = "Client has sended - " + s;
        m_ptxt->append(strMessage);

        //m_nNextBlockSize = 0;

        if (num == 1)   //SELECT
        {
            in >> table_name;
            sendToClientSEL(pClientSocket, table_name);
        }
        else if (num == 2)  //ADDING->ADD
        {
            in >> table_name;

            if(table_name == "students")
            {
                QString curs;
                in >> lastname >> name >> middlename >> curs >> id_group >> id_squad >> id_place >> amount_of_work >> salary;

                sendInsertToDBStudents(pClientSocket, lastname, name, middlename, curs, id_group, id_squad, id_place, amount_of_work, salary);
            }
            else if (table_name == "squads")
            {
                in >> newSquad;

                sendInsertToDBSquads(pClientSocket, newSquad);
            }
            else if (table_name == "stud_groups")
            {
                in >> newGroup;

                sendInsertToDBGroups(pClientSocket, newGroup);
            }
            else if (table_name == "work_place")
            {
                in >> type_of_construction >> address;

                sendInsertToDBWorkPlace(pClientSocket, type_of_construction, address);
            }
        }
        else if (num == 3)  //CHANGE
        {
            in >> table;
            sendToClientSELChanging(pClientSocket, table);
        }
        else if (num == 4)  //CHANGING
        {
            in >> table_name;

            if (table_name == "students")
            {
                in >> col_name;

                if(col_name == "group")
                {
                    in >> id_groupstr >> id;
                    sendUpdateToDB(pClientSocket, table_name, "", col_name, id_groupstr, id);
                }
                else if (col_name == "squad")
                {
                    in >> id_squadstr >> id;
                    sendUpdateToDB(pClientSocket, table_name, "", col_name, id_squadstr, id);
                }
                else if (col_name == "address")
                {
                    in >> id_addressstr >> id;
                    sendUpdateToDB(pClientSocket, table_name, "", col_name, id_addressstr, id);
                }
                else
                {
                    in >> change >> id;
                    sendUpdateToDB(pClientSocket, table_name, "", col_name, change, id);
                }
            }
            else
            {
                in >> col_name >> change >> id;
                sendUpdateToDB(pClientSocket, table_name, "", col_name, change, id);
            }
        }
        else if (num == 5)
        {
            //sendTables(pClientSocket);
        }
        else if (num == 6)  //authorizationCheck()
        {
            in >> login >> password;

            if (login == "user")
            {
                if (!createConnection(login))
                    return ;

                qDebug() << "User connected";
                sendTablesUser(pClientSocket);
            }
            else if (login == "admin")
            {
                if (!createConnection(login))
                    return ;

                qDebug() << "Admin connected";
                sendTablesAdmin(pClientSocket);
            }
        }
        else if (num == 7)
        {
            sendToClientSquads(pClientSocket);
        }
        else if (num == 8)
        {
            in >> table_name >> col_name >> id;
            sendDeleteToDB(table_name, col_name, id);
        }
        else if (num == 9)
        {
            in >> table_name >> id;
            sendToClientSELFilter(pClientSocket, table_name, id);
        }
        else if (num == 10)
        {
            in >> lastname >> name >> middlename;
            sendToClientSELFindStudent(pClientSocket, lastname, name, middlename);
        }
        else if (num == 11)
        {
            QString sign, filter;
            in >> sign >> filter;
            sendToClientSELGroupBy(pClientSocket, sign, filter);
        }
        else if (num == 12)
        {
            sendToClientSELGroupCount(pClientSocket);
        }
        else if (num == 13)
        {
            int id_student = -1, number;
            in >> id_student >> number;
            sendUpdateToDBSalary(pClientSocket, id_student, number);
        }
        else if (num == 14)
        {
            sendToCLientSELStudSquad(pClientSocket);
        }
        else if (num == 15)
        {
            sendToCLientSELStudAddress(pClientSocket);
        }
        else if (num == 16)
        {
            sendToCLientSELStudGroups(pClientSocket);
        }
        else if (num == 17)
        {
            sendToClientAVGADdress(pClientSocket);
        }
        else if (num == 18)
        {
            sendToClientAVGSalary(pClientSocket);
        }
        else if (num == 19)
        {
            sendToClientNorm(pClientSocket);
        }
        else
            sendToClient(pClientSocket, "Server Response: Received \"" + s + "\"");
    }

    m_nNextBlockSize = 0;
}

void MyServer::sendInsertToDBStudents(QTcpSocket* pSocket, QString lastname, QString name, QString middlename, QString curs, int id_group, int id_squad, int id_place, QString amount_of_work, float salary)
{
    if (login != "admin")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"admin\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }

    int work_hours = amount_of_work.toInt();
    qDebug() << "Часы в int: " << work_hours;
    QSqlQuery query;
    QString str = QString("CALL add_student('%0' ,'%1' ,'%2', '%3', %4, %5, %6, %7, %8);").arg(lastname).arg(name).arg(middlename).arg(curs).arg(id_group).arg(id_squad).arg(id_place).arg(work_hours).arg(salary);

    qDebug() << str;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }

    if (login == "user")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"user\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }
}

void MyServer::sendInsertToDBSquads(QTcpSocket* pSocket, QString newSquad)
{
    QSqlQuery query;
    QString str = QString("CALL add_squad('%0');").arg(newSquad);

    qDebug() << str;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        sendToClientSquads(pSocket);
    }
}

void MyServer::sendInsertToDBGroups(QTcpSocket* pSocket, QString newGroup)
{
    QString str = QString("CALL add_group('%0');").arg(newGroup);

    QSqlQuery query;


    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        sendToClientGroups(pSocket);
    }
}

void MyServer::sendInsertToDBWorkPlace(QTcpSocket* pSocket, QString type_of_construction, QString address)
{
    QSqlQuery query;
    QString str = QString("CALL add_work_place('%0', '%1');").arg(type_of_construction).arg(address);


    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        sendToClientWork(pSocket);
    }
}

void MyServer::sendUpdateToDB(QTcpSocket* pSocket, QString table_name, QString col_name_table,QString col_name, QString change, int id)
{
    if (login != "admin")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"admin\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }

    QSqlQuery query;

    //int intChange = NULL;

    if (table_name != "students")
    {
        if (table_name == "stud_groups")
        {
            col_name_table = "id_group";
        }
        else if (table_name == "squads")
        {
            col_name_table = "id_squad";
        }
        else if (table_name == "work_place")
        {
            col_name_table = "id_place";
        }

        QString query_str = QString("CALL update_table('%0', '%1', '%2', '%3', %4)").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);

        //query.prepare(query_str);

        qDebug() << query_str;

        if (!query.exec(query_str))
        {
            QSqlError error = query.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }
    else if (table_name == "students")
    {
        col_name_table = "id_stud";

        if (col_name == "group")
        {
            col_name = "id_group";
            //intChange = change.toInt();

            QString query_str = QString("CALL update_table('%0', '%1', '%2'::int, '%3', %4)").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);

            //query.prepare(query_str);

            qDebug() << query_str;

            if (!query.exec(query_str))
            {
                QSqlError error = query.lastError();
                qDebug() << "\nQuery error: " << error;
            }
            else
                sendToClientGroups(pSocket);
        }
        else if (col_name == "squad")
        {
            col_name = "id_squad";
            //intChange = change.toInt();

            QString query_str = QString("CALL update_table('%0', '%1', '%2'::int, '%3', %4)").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);

            //query.prepare(query_str);

            qDebug() << query_str;

            if (!query.exec(query_str))
            {
                QSqlError error = query.lastError();
                qDebug() << "\nQuery error: " << error;
            }
            else
                sendToClientSquads(pSocket);
        }
        else if (col_name == "address")
        {
            col_name = "id_place";
            //intChange = change.toInt();

            QString query_str = QString("CALL update_table('%0', '%1', '%2'::int, '%3', %4)").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);

            //query.prepare(query_str);

            qDebug() << query_str;

            if (!query.exec(query_str))
            {
                QSqlError error = query.lastError();
                qDebug() << "\nQuery error: " << error;
            }
            else
                sendToClientWork(pSocket);
        }
        else if (col_name == "salary")
        {
            QString query_str = QString("CALL update_table('%0', '%1', '%2'::numeric(12,2), '%3', %4)").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);

            //query.prepare(query_str);

            qDebug() << query_str;

            if (!query.exec(query_str))
            {
                QSqlError error = query.lastError();
                qDebug() << "\nQuery error: " << error;
            }
        }
        else if (col_name == "amount_of_work")
        {

            QString query_str = QString("CALL update_table('%0', '%1', '%2'::int, '%3', %4)").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);

            qDebug() << query_str;

            if (!query.exec(query_str))
            {
                QSqlError error = query.lastError();
                qDebug() << "\nQuery error: " << error;
            }
        }
        else
        {
            QString query_str = QString("CALL update_table('%0', '%1', '%2', '%3', %4)").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);

            //query.prepare(query_str);

            qDebug() << query_str;

            if (!query.exec(query_str))
            {
                QSqlError error = query.lastError();
                qDebug() << "\nQuery error: " << error;
            }
        }
    }

    if (login == "user")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"user\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }

    //QString query_str = QString("UPDATE %0 SET %1 = '%2' WHERE %3 = %4").arg(table_name).arg(col_name).arg(change).arg(col_name_table).arg(id);
}

void MyServer::sendDeleteToDB(QString table_name, QString col_name, int id)
{
    if (login != "admin")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"admin\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }

    QSqlQuery query;

    QString query_str = QString("CALL delete_row('%0', '%1', %2)").arg(table_name).arg(col_name).arg(id);

    qDebug() << query_str;

    if (!query.exec(query_str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }

    if (login == "user")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"admin\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }
}

void MyServer::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int num = 0;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT id_group, group_name FROM stud_groups;");

    out << quint16(0) << num;
    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << "\n" << arrBlock;

    pSocket->write(arrBlock);
}

void MyServer::sendToClientSELChanging(QTcpSocket* pSocket, QString table)     //To changing
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString str;

    if(table == "students")
        str = QString("SELECT * FROM selectStudents;");
    else
        str = QString("SELECT * FROM %0 ").arg(table);

    QString table_name = table;
    int num = 3;
    int table_num = NULL;

    if(table_name == "squads")
    {
        table_num = 1;
        str.append("order by id_squad asc;");
    }
    else if(table_name == "stud_groups")
    {
        table_num = 2;
        str.append("order by id_group asc;");
    }
    else if(table_name == "students")
    {
        table_num = 3;
    }
    else if(table_name == "work_place")
    {
        table_num = 4;
        str.append("order by id_place asc;");
    }

    qDebug() << "Str to changing: " << str;

    model->setQuery(str);

    QTableView *tableView = new QTableView(this);
    tableView->setModel(model);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num << table_num;

    out << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }
    qDebug() << "\nblock: " << block;


    out.device()->seek(0);
    out << quint16(block.size() - sizeof(quint16));

    qDebug() << "\nSize: " << quint16(block.size() - sizeof(quint16));

    pSocket->write(block);

    //sendToClientInfo(pSocket);
}

void MyServer::sendToClientSEL(QTcpSocket* pSocket, QString table_name)
{
    QByteArray arrBlock;
    arrBlock.clear();
    QString str;
    int num = 1;
    int table_num = NULL;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    if(table_name == "students")
        str = QString("SELECT * FROM selectStudents;");
    else
        str = QString("SELECT * FROM %0 ").arg(table_name);


    if(table_name == "squads")
    {
        table_num = 1;
        str.append("order by id_squad asc;");
    }
    else if(table_name == "stud_groups")
    {
        table_num = 2;
        str.append("order by id_group asc;");
    }
    else if(table_name == "students")
    {
        table_num = 3;
    }
    else if(table_name == "work_place")
    {
        table_num = 4;
        str.append("order by id_place asc;");
    }

    qDebug() << "\nSTR: " <<str;

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(str);
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);

    out1 << quint16(0) << num << table_num;
    out1 << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    qDebug() << "\nblock: " << block;

    out1.device()->seek(0);
    out1 << quint16(block.size() - sizeof(quint16));


    qDebug() << "\nSize: " << quint16(block.size() - sizeof(quint16));

    pSocket->write(block);
}

void MyServer::sendToClientSELFilter(QTcpSocket* pSocket, QString table, int id)
{
    QString str;
    int table_num = NULL;

    if (login != "admin")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"admin\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }

    if (table == "stud_groups")
    {
        str = QString("SELECT sg.group_name, s.lastname, s.name, s.middlename FROM stud_groups sg "
              "INNER JOIN students s ON s.id_group = sg.id_group "
               "INNER JOIN get_group_students(%0) gs ON gs.id_stud = s.id_stud;").arg(id);

        table_num = 1;
    }
    else if (table == "squads")
    {
        str = QString("SELECT sq.construction_team, s.lastname, s.name, s.middlename FROM squads sq "
              "INNER JOIN students s ON s.id_squad = sq.id_squad "
               "INNER JOIN get_squad_students(%0) gq ON gq.id_stud = s.id_stud;").arg(id);

        table_num = 2;
    }
    else
        return;

    int num = 11;
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(str);

    out1 << quint16(0) << num << table_num;
    out1 << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    qDebug() << "\nblock: " << block;

    out1.device()->seek(0);
    out1 << quint16(block.size() - sizeof(quint16));


    qDebug() << "\nSize: " << quint16(block.size() - sizeof(quint16));

    pSocket->write(block);

    if (login == "user")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"user\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }
}

void MyServer::sendToClientSELFindStudent(QTcpSocket* pSocket, QString lastname, QString name, QString middlename)
{
    if (login != "admin")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"admin\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }

    QString str = QString("SELECT * FROM get_student_info('%0', '%1', '%2');").arg(lastname).arg(name).arg(middlename);

    int num = 12;

    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(str);
    qDebug() << str;
    qDebug() << model->rowCount() << model->columnCount();

    out1 << quint16(0) << num;
    out1 << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            qDebug() << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    qDebug() << "\nblock: " << block;

    out1.device()->seek(0);
    out1 << quint16(block.size() - sizeof(quint16));


    qDebug() << "\nSize: " << quint16(block.size() - sizeof(quint16));

    pSocket->write(block);

    if (login == "user")
    {
        QSqlQuery query1;
        QString str1 = QString("SET ROLE \"user\";");
        qDebug() << str1;

        if(!query1.exec(str1))
        {
            QSqlError error = query1.lastError();
            qDebug() << "\nQuery error: " << error;
        }
    }
}

void MyServer::sendToClientSELGroupBy(QTcpSocket* pSocket, QString sign, QString filter)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    QSqlQuery query;

    if (sign == "Без фильтра" || filter == "")
    {
        QString str = QString("SELECT sg.group_name, AVG(s.salary) FROM students s LEFT JOIN stud_groups sg ON s.id_group = sg.id_group "
                              "GROUP BY sg.group_name ORDER BY AVG(s.salary);");

        qDebug() << str;

        int num = 13;

        QByteArray block;
        QDataStream out1(&block, QIODevice::WriteOnly);
        out1.setVersion(QDataStream::Qt_6_4);

        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << quint16(0) << num;
        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        qDebug() << "\nblock: " << block;

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));


        qDebug() << "\nSize: " << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
    else
    {
        QString str = QString("SELECT sg.group_name, AVG(s.salary) FROM students s LEFT JOIN stud_groups sg ON s.id_group = sg.id_group "
                              "GROUP BY sg.group_name HAVING AVG(s.salary) %0 %1 ORDER BY AVG(s.salary);").arg(sign).arg(filter);

        qDebug() << str;

        int num = 13;

        QByteArray block;
        QDataStream out1(&block, QIODevice::WriteOnly);
        out1.setVersion(QDataStream::Qt_6_4);

        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << quint16(0) << num;
        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        qDebug() << "\nblock: " << block;

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));


        qDebug() << "\nSize: " << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}

void MyServer::sendToClientSELGroupCount(QTcpSocket* pSocket)
{
    QString str = QString("SELECT "
                          "sg.group_name, "
                          "SUM(CASE WHEN s.curs = '1 курс' THEN 1 ELSE 0 END) AS first_year_students, "
                          "SUM(CASE WHEN s.curs = '2 курс' THEN 1 ELSE 0 END) AS second_year_students, "
                          "SUM(CASE WHEN s.curs = '3 курс' THEN 1 ELSE 0 END) AS third_year_students, "
                          "SUM(CASE WHEN s.curs = '4 курс' THEN 1 ELSE 0 END) AS fourth_year_students, "
                          "COUNT(s.id_stud) AS total_students "
                          "FROM "
                          "stud_groups sg JOIN students s "
                          "ON sg.id_group = s.id_group "
                          "GROUP BY sg.group_name;");

    qDebug() << str;

    int num = 14;

    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);

    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(str);

    out1 << quint16(0) << num;
    out1 << model->rowCount() << model->columnCount();

    for (int row = 0; row < model->rowCount(); row++)
    {
        for (int column = 0; column < model->columnCount(); column++)
        {
            out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
        }
    }

    out1.device()->seek(0);
    out1 << quint16(block.size() - sizeof(quint16));

    pSocket->write(block);
}

void MyServer::sendUpdateToDBSalary(QTcpSocket* pSocket, int id_student, int number)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 3;

    QString str = QString("CALL increase_salary_procadure(%0, %1);").arg(id_student).arg(number);
    QSqlQuery query;
    qDebug() << str;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        sendToClientSELChanging(pSocket, "students");
    }
}

void MyServer::sendToCLientSELStudSquad(QTcpSocket* pSocket)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 15;

    out1 << quint16(0) << num;

    QString str = QString("SELECT s.name, s.lastname, s.middlename, s.curs,"
                          "(SELECT construction_team FROM squads sq WHERE sq.id_squad = s.id_squad) AS squad_name FROM students s ORDER BY s.id_stud;");
    QSqlQuery query;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}

void MyServer::sendToCLientSELStudAddress(QTcpSocket* pSocket)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 16;

    out1 << quint16(0) << num;

    QString str = QString("SELECT s.name, s.lastname, s.middlename, s.curs, wp.address "
                          "FROM students s LEFT JOIN work_place wp "
                          "ON wp.id_place = (SELECT id_place FROM students s2 WHERE s2.id_stud = s.id_stud) "
                          "ORDER BY s.id_stud;");
    QSqlQuery query;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}

void MyServer::sendToCLientSELStudGroups(QTcpSocket* pSocket)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 17;

    out1 << quint16(0) << num;

    QString str = QString("SELECT s.name, s.lastname, s.middlename, s.curs FROM students s WHERE (SELECT stud_count FROM stud_groups sg WHERE sg.id_group = s.id_group) > 1;");
    QSqlQuery query;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}

void MyServer::sendToClientAVGADdress(QTcpSocket* pSocket)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 18;

    out1 << quint16(0) << num;

    QString str = QString("SELECT type_of_construction, address, (SELECT AVG(amount_of_work) FROM students s WHERE wp.id_place = s.id_place) AS avg_time FROM work_place wp;");
    QSqlQuery query;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}

void MyServer::sendToClientAVGSalary(QTcpSocket* pSocket)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 19;

    out1 << quint16(0) << num;

    QString str = QString("SELECT construction_team, (SELECT AVG(salary) FROM students s WHERE s.id_squad = sq.id_squad) AS avg_salary FROM squads sq;");
    QSqlQuery query;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}

void MyServer::sendToClientMAX(QTcpSocket* pSocket)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 20;

    out1 << quint16(0) << num;

    QString str = QString("SELECT group_name FROM stud_groups sg WHERE (SELECT MAX(amount_of_work) "
                          "FROM students s WHERE sg.id_group = s.id_group) > 8 AND "
                          "(SELECT COUNT(*) FROM students s WHERE sg.id_group = s.id_group) > 1;");
    QSqlQuery query;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}

void MyServer::sendToClientNorm(QTcpSocket* pSocket)
{
    QByteArray block;
    QDataStream out1(&block, QIODevice::WriteOnly);
    out1.setVersion(QDataStream::Qt_6_4);
    int num = 20;

    out1 << quint16(0) << num;

    QString str = QString("SELECT group_name FROM stud_groups sg "
                          "WHERE (SELECT MAX(amount_of_work) "
                          "FROM students s WHERE sg.id_group = s.id_group) > 8 "
                          "AND (SELECT COUNT(*) FROM students s WHERE sg.id_group = s.id_group) > 1;");
    QSqlQuery query;

    if(!query.exec(str))
    {
        QSqlError error = query.lastError();
        qDebug() << "\nQuery error: " << error;
    }
    else
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);
        model->setQuery(str);

        out1 << model->rowCount() << model->columnCount();

        for (int row = 0; row < model->rowCount(); row++)
        {
            for (int column = 0; column < model->columnCount(); column++)
            {
                out1 << model->data(model->index(row, column), Qt::DisplayRole).toString();
            }
        }

        out1.device()->seek(0);
        out1 << quint16(block.size() - sizeof(quint16));

        pSocket->write(block);
    }
}
