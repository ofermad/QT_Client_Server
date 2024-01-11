
#ifndef DATABASECONN_H
#define DATABASECONN_H

#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


inline bool createConnection(QString login)
{
    qDebug() << QSqlDatabase::drivers();

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");

    db.setDatabaseName("StudStroitel");
    db.setHostName("localhost");
    db.setUserName("postgres");
    db.setPassword("user");

    QString role = QString("options='-c session_authorization=%0'").arg(login);
    qDebug() << role;

    //db.setConnectOptions(role);

    //QSqlQuery query;
    //QString str = QString("SET ROLE \"%0\";").arg(login);

    //qDebug() << str;

    if (!db.open())
    {
        //QMessageBox::warning(0, "Ошибка БД", db.lastError().text());
        qDebug() << "Error connection: " << db.lastError().text();
        return false;
    }
    else
    {
        //QMessageBox::information(0, "Успешно", "Соединение с БД установлено");

        /*if(!query.exec(str))
        {
            QSqlError error = query.lastError();
            qDebug() << "\nQuery error: " << error;
        }*/

        qDebug() << "DB connected";
        return true;
    }
}

#endif // DATABASECONN_H
