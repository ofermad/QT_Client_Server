#include "mainwindow.h"
#include "adding.h"
#include "search.h"
#include "ui_adding.h"
#include "ui_changing.h"
#include "ui_mainwindow.h"
#include "ui_search.h"
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QTime>
#include <mainwindow.h>
#include <QTextEdit>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QCloseEvent>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_nNextBlockSize(0), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->pushButton_5->hide();
    ui->pushButton_7->hide();
    ui->pushButton_8->hide();
    ui->label->hide();
    ui->textEdit->setReadOnly(true);

    secondWindow = new adding();
    thirdWindow = new changing();
    loginWindow = new authorization();
    searchWindow = new search();

    m_pTcpSocket = new QTcpSocket(this);

    secondWindow->TcpSocket(m_pTcpSocket);
    thirdWindow->TcpSocket(m_pTcpSocket);
    loginWindow->TcpSocket(m_pTcpSocket);
    searchWindow->TcpSocket(m_pTcpSocket);

    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,         SLOT(slotError(QAbstractSocket::SocketError))
            );

    connect(loginWindow, &authorization::textValid, this, &MainWindow::authorizationCheck);

    loginWindow->show();


    qDebug() << m_pTcpSocket;
}

void MainWindow::authorizationCheck(QString login, QString password)
{
    this->show();

    m_pTcpSocket->connectToHost("localhost", 2323);

    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    int num = 6;
    out << quint16(0) << num << login << password;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << arrBlock;
    m_pTcpSocket->write(arrBlock);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Закрыть окно", "Вы уверены, что хотите закрыть окно?\nВсе окна будут закрыты!",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        event->accept();
        QApplication::closeAllWindows();
    } else
    {
        event->ignore();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    m_pTcpSocket->connectToHost("localhost", 2323);
    secondWindow->ui->comboBox->clear();
    secondWindow->ui->comboBox_3->clear();
    secondWindow->ui->comboBox_4->clear();

    loginWindow->Login();
}

void MainWindow::slotConnected()
{
    ui->textEdit->append("Received the connected() signal");
}

void MainWindow::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_6_4);

    for (;;) {
        if (!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
            qDebug() << "\nm_nNextBlockSize: " << m_nNextBlockSize;
        }

        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }
        //int k = 0; //количество строк
        //int num = 0; //ключ для каждой операции
        //QString str;

        int row_count, column_count, num = -1, table_num;

        in >> num;

        qDebug() << "\nnum sended: " << num << "\n";

        if (num == 1)
        {
            in >> table_num >> row_count >> column_count;
            //qDebug() << table_num << row_count << column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            if (table_num == 1)
                model->setHorizontalHeaderLabels(QStringList() << "id_squad" << "construction_team" << "stud_count");
            else if (table_num == 2)
                model->setHorizontalHeaderLabels(QStringList() << "id_group" << "group_name" << "stud_count");
            else if (table_num == 3)
                model->setHorizontalHeaderLabels(QStringList() << "id_stud" << "lastname" << "name" << "middlename" <<  "curs" << "group"<<"squad"<<"type_of_construction"<< "address"<<"amount_of_work"<<"salary" << "modification_date");
            else if (table_num == 4)
                model->setHorizontalHeaderLabels(QStringList() << "id_place" << "type_of_construction" << "address");


            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);

            ui->tableView->setColumnHidden(0, true);
        }
        else if (num == 0)      //INFO
        {
            in >> row_count >> column_count;
            //qDebug() << "\nGroups rows: " << row_count;

            for (int row = 0; row < row_count; row++)
            {
                QString cell_content;
                QString cell_content1;

                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapGroups.insert(cell_content1, cell_content.toInt());

                //qDebug() << cell_content << cell_content1;

                //QString searchKey = cell_content1;
                //int value = myMap.value(searchKey);
                //qDebug() << "Номер строки \"" << searchKey << "\" равен " << value;

            }

            secondWindow->foreignMapAddingGroups = myMapGroups;
            thirdWindow->foreignMapChangingGroups = myMapGroups;

            for (int i = 1; i <= secondWindow->foreignMapAddingGroups.count(); ++i)
                secondWindow->ui->comboBox->addItem(secondWindow->foreignMapAddingGroups.key(i), "");


            in >> row_count >> column_count;

            for (int row = 1; row <= row_count; row++)
            {
                QString cell_content;
                QString cell_content1;


                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapSquads.insert(cell_content1, cell_content.toInt());
            }

            secondWindow->foreignMapAddingSquads = myMapSquads;
            thirdWindow->foreignMapChangingSquads = myMapSquads;

            for (int i = 1; i <= secondWindow->foreignMapAddingSquads.count(); ++i)
                secondWindow->ui->comboBox_3->addItem(secondWindow->foreignMapAddingSquads.key(i), "");

            in >> row_count >> column_count;

            for (int row = 1; row <= row_count; row++)
            {
                QString cell_content;
                QString cell_content1;


                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapWork.insert(cell_content1, cell_content.toInt());
            }

            secondWindow->foreignMapAddingWork = myMapWork;
            thirdWindow->foreignMapChangingWork = myMapWork;

            for (int i = 1; i <= secondWindow->foreignMapAddingWork.count(); ++i)
                secondWindow->ui->comboBox_4->addItem(secondWindow->foreignMapAddingWork.key(i), "");

        }
        else if (num == 3)
        {
            in >> table_num >> row_count >> column_count;
            //qDebug() << table_num << row_count << column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            if (table_num == 1)
                model->setHorizontalHeaderLabels(QStringList() << "id_squad" << "construction_team" << "stud_count");
            else if (table_num == 2)
                model->setHorizontalHeaderLabels(QStringList() << "id_group" << "group_name" << "stud_count");
            else if (table_num == 3)
                model->setHorizontalHeaderLabels(QStringList() << "id_stud" << "lastname" << "name" << "middlename" << "curs" << "group"<<"squad"<<"type_of_construction"<< "address"<<"amount_of_work"<<"salary"<< "modification_date");
            else if (table_num == 4)
                model->setHorizontalHeaderLabels(QStringList() << "id_place" << "type_of_construction" << "address");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            thirdWindow->ui->tableView->setColumnHidden(0, true);

            thirdWindow->recivedModel(model);
        }
        else if (num == 5)
        {
            secondWindow->ui->comboBox->clear();
            secondWindow->ui->comboBox_2->clear();
            secondWindow->ui->comboBox_3->clear();
            secondWindow->ui->comboBox_4->clear();

            thirdWindow->ui->comboBox_2->clear();
            thirdWindow->ui->comboBox->clear();

            ui->comboBox->clear();
            ui->comboBox_2->clear();
            ui->comboBox_3->clear();
            //ui->comboBox_4->clear();

            thirdWindow->ui->comboBox_2->blockSignals(true);
            //thirdWindow->ui->comboBox->blockSignals(true);


            in >> row_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                QString cell_content;
                in >> cell_content;

                qDebug () << cell_content;

                QStandardItem *item = new QStandardItem(cell_content);

                row_items.append(item);

                model->appendRow(row_items);
            }

            ui->comboBox->setModel(model);
            secondWindow->ui->comboBox_2->setModel(model);
            thirdWindow->ui->comboBox->setModel(model);

            in >> row_count >> column_count;
            //qDebug() << "\nGroups rows: " << row_count;

            for (int row = 0; row < row_count; row++)
            {
                QString cell_content;
                QString cell_content1;

                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapGroups.insert(cell_content1, cell_content.toInt());
            }

            secondWindow->foreignMapAddingGroups = myMapGroups;
            thirdWindow->foreignMapChangingGroups = myMapGroups;

            QMap<QString, int>::iterator itGroups = myMapGroups.begin();

            qDebug() << "\n";

            while (itGroups != myMapGroups.end())
            {
                secondWindow->ui->comboBox->addItem(itGroups.key());
                ui->comboBox_2->addItem(itGroups.key());
                //thirdWindow->ui->comboBox_2->addItem(itGroups.key());
                qDebug() << itGroups.key();
                ++itGroups;
            }

            in >> row_count >> column_count;

            for (int row = 1; row <= row_count; row++)
            {
                QString cell_content;
                QString cell_content1;


                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapSquads.insert(cell_content1, cell_content.toInt());
            }

            secondWindow->foreignMapAddingSquads = myMapSquads;
            thirdWindow->foreignMapChangingSquads = myMapSquads;

            QMap<QString, int>::iterator itSquads = myMapSquads.begin();

            while (itSquads != myMapSquads.end())
            {
                secondWindow->ui->comboBox_3->addItem(itSquads.key());
                ui->comboBox_3->addItem(itSquads.key());
                //thirdWindow->ui->comboBox_2->addItem(itSquads.key());
                qDebug() << itSquads.key();
                ++itSquads;
            }

            in >> row_count >> column_count;

            for (int row = 1; row <= row_count; row++)
            {
                QString cell_content;
                QString cell_content1;


                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapWork.insert(cell_content1, cell_content.toInt());
            }

            secondWindow->foreignMapAddingWork = myMapWork;
            thirdWindow->foreignMapChangingWork = myMapWork;

            QMap<QString, int>::iterator itWork = myMapWork.begin();

            while (itWork != myMapWork.end())
            {
                secondWindow->ui->comboBox_4->addItem(itWork.key());
                //thirdWindow->ui->comboBox_2->addItem(itWork.key());
                qDebug() << itWork.key();
                ++itWork;
            }

            thirdWindow->ui->comboBox_2->blockSignals(false);
            thirdWindow->ui->comboBox->blockSignals(false);
        }
        else if (num == 8)      //WORK
        {
            in >> row_count >> column_count;

            thirdWindow->ui->comboBox_2->blockSignals(true);

            secondWindow->ui->comboBox_4->clear();
            secondWindow->foreignMapAddingWork.clear();

            thirdWindow->foreignMapChangingWork.clear();

            for (int row = 1; row <= row_count; row++)
            {
                QString cell_content;
                QString cell_content1;


                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapWork.insert(cell_content1, cell_content.toInt());
            }


            secondWindow->foreignMapAddingWork = myMapWork;
            thirdWindow->foreignMapChangingWork = myMapWork;

            QMap<QString, int>::iterator itWork = myMapWork.begin();

            while (itWork != myMapWork.end())
            {
                secondWindow->ui->comboBox_4->addItem(itWork.key());
                qDebug() << itWork.key();
                ++itWork;
            }

            thirdWindow->ui->comboBox_2->blockSignals(false);
        }
        else if (num == 9)      //SQUADS
        {
            thirdWindow->ui->comboBox_2->blockSignals(true);

            in >> row_count >> column_count;

            secondWindow->ui->comboBox_3->clear();
            secondWindow->foreignMapAddingSquads.clear();

            thirdWindow->foreignMapChangingSquads.clear();

            for (int row = 1; row <= row_count; row++)
            {
                QString cell_content;
                QString cell_content1;


                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapSquads.insert(cell_content1, cell_content.toInt());
            }

            secondWindow->foreignMapAddingSquads = myMapSquads;
            thirdWindow->foreignMapChangingSquads = myMapSquads;

            QMap<QString, int>::iterator itSquads = myMapSquads.begin();

            while (itSquads != myMapSquads.end())
            {
                secondWindow->ui->comboBox_3->addItem(itSquads.key());
                qDebug() << itSquads.key();
                ++itSquads;
            }

            thirdWindow->ui->comboBox_2->blockSignals(false);
        }
        else if (num == 10)     //GROUPS
        {
            thirdWindow->ui->comboBox_2->blockSignals(true);

            in >> row_count >> column_count;
            //qDebug() << "\nGroups rows: " << row_count;

            secondWindow->ui->comboBox->clear();
            secondWindow->foreignMapAddingGroups.clear();

            thirdWindow->foreignMapChangingGroups.clear();

            for (int row = 0; row < row_count; row++)
            {
                QString cell_content;
                QString cell_content1;

                in >> cell_content >> cell_content1;

                qDebug() << cell_content << cell_content1;

                myMapGroups.insert(cell_content1, cell_content.toInt());

                //qDebug() << cell_content << cell_content1;

                //QString searchKey = cell_content1;
                //int value = myMap.value(searchKey);
                //qDebug() << "Номер строки \"" << searchKey << "\" равен " << value;

            }

            secondWindow->foreignMapAddingGroups = myMapGroups;
            thirdWindow->foreignMapChangingGroups = myMapGroups;

            QMap<QString, int>::iterator itGroups = myMapGroups.begin();

            while (itGroups != myMapGroups.end())
            {
                secondWindow->ui->comboBox->addItem(itGroups.key());
                qDebug() << itGroups.key();
                ++itGroups;
            }

            thirdWindow->ui->comboBox_2->blockSignals(false);
        }
        else if (num == 11)     //Кто какой группе принадлежит
        {
            in >> table_num >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            if (table_num == 1)
                model->setHorizontalHeaderLabels(QStringList() << "group" << "lastname" << "name" << "middlename");
            else if (table_num == 2)
                model->setHorizontalHeaderLabels(QStringList() << "squad" << "lastname" << "name" << "middlename");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setColumnHidden(0, false);

            ui->tableView->setModel(model);

            ui->tableView->setColumnHidden(0, false);

        }
        else if (num == 12)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "id_stud" << "lastname" << "name" << "middlename" << "curs" << "group"<<"squad"<<"type_of_construction"<< "address"<<"amount_of_work"<<"salary"<< "modification_date");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }
            searchWindow->ui->tableView->setColumnHidden(0, true);

            searchWindow->ui->tableView->setModel(model);

            searchWindow->ui->tableView->setColumnHidden(0, true);

        }
        else if (num == 13)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "group" << "avg_salary");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        else if (num ==14)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "group" << "first_year_students" << "second_year_students" << "third_year_students" << "fourth_year_students" << "total_students");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        else if (num == 15)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "name" << "lastname" << "middlename" << "curs" << "construction_team");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        else if (num == 16)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "name" << "lastname" << "middlename" << "curs" << "address");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        else if (num == 17)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "name" << "lastname" << "middlename" << "curs" << "group");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        else if (num == 18)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "type_of_construction" << "address" << "avg_time");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        else if (num == 19)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "construction_team" << "salary");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        else if (num == 20)
        {
            in >> row_count >> column_count;

            QStandardItemModel *model = new QStandardItemModel(this);

            model->setHorizontalHeaderLabels(QStringList() << "group_name");

            for (int row = 0; row < row_count; row++)
            {
                QList<QStandardItem *> row_items;

                for (int column = 0; column < column_count; column++)
                {
                    QString cell_content;
                    in >> cell_content;

                    QStandardItem *item = new QStandardItem(cell_content);

                    row_items.append(item);
                }

                model->appendRow(row_items);
            }

            ui->tableView->setModel(model);
            ui->tableView->setColumnHidden(0, false);
        }
        m_nNextBlockSize = 0;
    }

    //m_nNextBlockSize = 0;
}

void MainWindow::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
        "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                         "The host was not found." :
                         err == QAbstractSocket::RemoteHostClosedError ?
                             "The remote host is closed." :
                             err == QAbstractSocket::ConnectionRefusedError ?
                                 "The connection was refused." :
                                 QString(m_pTcpSocket->errorString())
                     );
    ui->textEdit->append(strError);
}

void MainWindow::slotSendToServer()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    out << quint16(0) << QTime::currentTime();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << arrBlock;
    m_pTcpSocket->write(arrBlock);
}

void MainWindow::slotSendToServerSEL()
{
    /*
    QByteArray  arrBlock;
    QString str = "SELECT";
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    //qDebug() << arrBlock.size();
    out << quint16(arrBlock.size() - sizeof(quint16));
    //qDebug() << arrBlock;
    m_pTcpSocket->write(arrBlock);*/
}



void MainWindow::on_pushButton_clicked() //SELECT
{
    QByteArray  arrBlock;
    QString table_name = ui->comboBox->currentText();
    int num = 1;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num << table_name;
    out.device()->seek(0);
    //qDebug() << arrBlock.size();
    out << quint16(arrBlock.size() - sizeof(quint16));
    //qDebug() << arrBlock;
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_3_clicked() //ADD
{
    secondWindow->show();
}


void MainWindow::on_pushButton_4_clicked() //CHANGE
{
    QByteArray  arrBlock;
    int num = 3;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    qDebug() << thirdWindow->ui->comboBox->currentText();

    out << quint16(0) << num << thirdWindow->ui->comboBox->currentText();
    out.device()->seek(0);
    //qDebug() << arrBlock.size();
    out << quint16(arrBlock.size() - sizeof(quint16));
    //qDebug() << arrBlock;
    m_pTcpSocket->write(arrBlock);

    thirdWindow->show();
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (ui->comboBox->currentText() == "stud_groups")
    {
        ui->label->setText("Вывести студентов из выбранной группы");
        ui->pushButton_8->show();
        ui->comboBox_2->show();
        ui->comboBox_3->hide();
        ui->comboBox_4->hide();
        ui->pushButton_7->hide();
        ui->pushButton_12->hide();
        ui->pushButton_13->hide();
        ui->pushButton_14->hide();
        ui->lineEdit->hide();
        ui->pushButton_5->show();
        ui->pushButton_9->hide();
        ui->pushButton_10->hide();
        ui->pushButton_11->hide();
    }
    else if (ui->comboBox->currentText() == "squads")
    {
        ui->label->setText("Вывести студентов из выбранного отряда");
        ui->comboBox_2->hide();
        ui->comboBox_3->show();
        ui->comboBox_4->hide();
        ui->pushButton_8->hide();
        ui->pushButton_7->hide();
        ui->pushButton_12->hide();
        ui->pushButton_13->hide();
        ui->pushButton_14->hide();
        ui->lineEdit->hide();
        ui->pushButton_5->show();
        ui->pushButton_9->hide();
        ui->pushButton_10->hide();
        ui->pushButton_11->hide();
    }
    else if (ui->comboBox->currentText() == "students")
    {
        ui->label->hide();
        ui->pushButton_7->show();
        ui->comboBox_4->show();
        ui->lineEdit->show();
        ui->pushButton_9->show();
        ui->pushButton_10->show();
        ui->pushButton_11->show();
        ui->pushButton_12->show();
        ui->pushButton_13->show();
        ui->pushButton_14->show();
        ui->pushButton_8->hide();
        ui->comboBox_3->hide();
        ui->comboBox_2->hide();
        ui->pushButton_5->hide();
    }
    else
    {

        ui->label->hide();
        ui->pushButton_7->hide();
        ui->comboBox_2->hide();
        ui->comboBox_3->hide();
        ui->pushButton_9->hide();
        ui->pushButton_10->hide();
        ui->pushButton_11->hide();
        ui->pushButton_12->hide();
        ui->pushButton_13->hide();
        ui->pushButton_14->hide();
        ui->pushButton_8->hide();
        ui->pushButton_5->hide();
        ui->lineEdit->hide();
        ui->comboBox_4->hide();
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if (ui->comboBox_2->currentText() == "Группа не выбрана" && ui->comboBox_3->currentText() == "Отряд не выбран")
    {
        QMessageBox::warning(0, "Ошибка", "Фильтр не выбран");
        return;
    }

    int id = -1;

    if (ui->comboBox->currentText() == "stud_groups")
    {
        if (!myMapGroups.contains(ui->comboBox_2->currentText()))
        {
            qDebug() << "Такой группы не существует";
            return ;
        }
        else
        {
            id = myMapGroups.take(ui->comboBox_2->currentText());
            qDebug() << "id_group" << id;
        }
    }
    else if (ui->comboBox->currentText() == "squads")
    {
        if (!myMapSquads.contains(ui->comboBox_3->currentText()))
        {
            qDebug() << "Такой группы не существует";
            return ;
        }
        else
        {
            id = myMapSquads.take(ui->comboBox_3->currentText());
            qDebug() << "id_squad" << id;
        }
    }

    QByteArray  arrBlock;
    QString table_name = ui->comboBox->currentText();

    int num = 9;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num << table_name << id;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_6_clicked()
{
    searchWindow->show();
}


void MainWindow::on_pushButton_7_clicked()
{
    QByteArray  arrBlock;
    QString sign = ui->comboBox_4->currentText();
    QString filter = ui->lineEdit->text();

    QRegularExpression re("^[0-9]+$");

    if (!re.match(filter).hasMatch() && filter != "")
    {
        QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");
        return;
    }

    int num = 11;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num << sign << filter;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_8_clicked()
{
    QByteArray  arrBlock;

    int num = 12;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_9_clicked()
{
    QByteArray  arrBlock;

    int num = 14;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_10_clicked()
{
    QByteArray  arrBlock;

    int num = 15;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_11_clicked()
{
    QByteArray  arrBlock;

    int num = 16;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_12_clicked()
{
    QByteArray  arrBlock;

    int num = 17;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_13_clicked()
{
    QByteArray  arrBlock;

    int num = 18;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}


void MainWindow::on_pushButton_14_clicked()
{
    QByteArray  arrBlock;

    int num = 19;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}

