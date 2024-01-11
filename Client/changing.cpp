#include "changing.h"
#include "ui_changing.h"
#include <QRegularExpression>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QKeyEvent>


changing::changing(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changing)
{
    ui->setupUi(this);

    //ui->comboBox_2->addItem("Нужная ячейка не выбрана");
}

changing::~changing()
{
    delete ui;
}

void changing::TcpSocket(QTcpSocket *socket)
{
    foreignSocket = socket;
    qDebug() << "Socket from \'changing\': " << foreignSocket;

    //connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox_currentIndexChanged(int)));
}

void changing::recivedModel(QStandardItemModel *model)
{
    recievedmodel = model;
    ui->tableView->setModel(recievedmodel);
    ui->tableView->setColumnHidden(0, true);

    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged, this, &changing::handleDataChanged);
    connect(ui->tableView->selectionModel(), &QItemSelectionModel::currentChanged, [&](const QModelIndex &current)
    {
        row = current.row();
        column = current.column();

        qDebug() << row << column;

        if (recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole) == "group")
        {
            flag = 1;
            ui->comboBox_2->clear();

            QMap<QString, int>::iterator itGroups = foreignMapChangingGroups.begin();

            while (itGroups != foreignMapChangingGroups.end())
            {
                ui->comboBox_2->addItem(itGroups.key());
                qDebug() << itGroups.key();
                ++itGroups;
            }

            ui->tableView->model()->data(ui->tableView->model()->index(row, column));
            qDebug() << ui->tableView->model()->data(ui->tableView->model()->index(row, column)) << "\n";

            int index = ui->comboBox_2->findData(ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString(), Qt::CaseInsensitive);
            if (index != -1)
                ui->comboBox_2->setCurrentIndex(index);

            flag = 0;
        }
        else if (recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole) == "squad")
        {
            flag = 1;
            ui->comboBox_2->clear();

            QMap<QString, int>::iterator itSquads = foreignMapChangingSquads.begin();

            while (itSquads != foreignMapChangingSquads.end())
            {
                ui->comboBox_2->addItem(itSquads.key());
                qDebug() << itSquads.key();
                ++itSquads;
            }

            ui->tableView->model()->data(ui->tableView->model()->index(row, column));
            qDebug() << ui->tableView->model()->data(ui->tableView->model()->index(row, column)) << "\n";

            int index = ui->comboBox_2->findData(ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString(), Qt::CaseInsensitive);
            if (index != -1)
                ui->comboBox_2->setCurrentIndex(index);

            flag = 0;
        }
        else if (recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole) == "address")
        {
            flag = 1;
            ui->comboBox_2->clear();

            QMap<QString, int>::iterator itWork = foreignMapChangingWork.begin();

            while (itWork != foreignMapChangingWork.end())
            {
                ui->comboBox_2->addItem(itWork.key());
                qDebug() << itWork.key();
                ++itWork;
            }

            ui->tableView->model()->data(ui->tableView->model()->index(row, column));
            qDebug() << ui->tableView->model()->data(ui->tableView->model()->index(row, column)) << "\n";

            int index = ui->comboBox_2->findData(ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString(), Qt::CaseInsensitive);
            if (index != -1)
                ui->comboBox_2->setCurrentIndex(index);

            flag = 0;
        }
        else
        {
            flag = 1;
            ui->comboBox_2->clear();
            ui->comboBox_2->addItem("Нужная ячейка не выбрана");
        }

        qDebug() << "Selected cell: " << row << ", " << column;
    });

    qDebug() << "Model1: " << ui->tableView->model();
}

void changing::on_comboBox_currentIndexChanged(int index)
{
    QByteArray  arrBlock;
    int num = 3;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num << ui->comboBox->itemText(index);
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    flag = 1;

    if (ui->comboBox->currentText() == "work_place")
    {
        ui->pushButton->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
        ui->comboBox_2->hide();
    }
    else if (ui->comboBox->currentText() == "stud_groups")
    {
        ui->pushButton->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
        ui->comboBox_2->hide();
    }
    else if (ui->comboBox->currentText() == "squads")
    {
        ui->pushButton->hide();
        ui->pushButton_3->hide();
        ui->pushButton_4->hide();
        ui->comboBox_2->hide();
    }
    else if (ui->comboBox->currentText() == "students")
    {
        ui->pushButton->show();
        ui->pushButton_3->show();
        ui->pushButton_4->show();
        ui->comboBox_2->show();
    }

    foreignSocket->write(arrBlock);
}

bool onlyRussianLettersChanging(QString text)
{
    static QRegularExpression russianAlphabet("^[А-Яа-я]+$");
    return russianAlphabet.match(text).hasMatch();
}

void changing::handleDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QVector<int>& roles)
{
    qDebug() << "\nDATA CHANGED\n";
    qDebug() << "\nhandleDataChanged flag: " << flag;

    if (ui->comboBox->currentText() == "students" && (topLeft.column() == 4 || topLeft.column() == 5 || topLeft.column() == 6 || topLeft.column() == 7))
    {
        return;
    }

    Q_UNUSED(roles);

    QModelIndex indexs;
    QString datas, col_name;
    QString table_name = ui->comboBox->currentText();
    int id;

    for (int row = topLeft.row(); row <= bottomRight.row(); ++row)
    {
        for (int column = topLeft.column(); column <= bottomRight.column(); ++column)
        {
            QModelIndex index = ui->tableView->model()->index(row, column);

            QVariant data = ui->tableView->model()->data(index);

            indexs = index;
            datas = data.toString();
            id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();
            col_name = recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();

            qDebug() << "\nNew data: " << data.toString();

            qDebug() << "Column name: " << recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
            qDebug() << "Id: " << recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toString();
        }
    }

    bool onlyRussianLettersChanging(QString text);

    if (col_name != "salary" && col_name != "amount_of_work")
    {
        if (!onlyRussianLettersChanging(datas))
        {
            qDebug() << "Model2: " << ui->tableView->model();

            QByteArray  arrBlock;
            int num = 3;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);

            out << quint16(0) << num;
            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));

            int result = QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");

            qDebug () << "\nresult: " << result;

            if(result == 1024)
            {
                //foreignSocket->write(arrBlock);
                qDebug() << "\nWrong input!";
                return ;
            }
        }
        else
        {
            QByteArray  arrBlock;
            int num = 4;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);

            qDebug() << table_name << col_name << datas << id;
            out << quint16(0) << num << table_name << col_name << datas << id;
            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));

            foreignSocket->write(arrBlock);
        }
    }
    else if (col_name == "salary")
    {
        QRegularExpression reSal("[0-9]*\\.?[0-9]+");

        if (reSal.match(datas).hasMatch())
        {
            QByteArray  arrBlock;
            int num = 4;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);

            qDebug() << table_name << col_name << datas << id;
            out << quint16(0) << num << table_name << col_name << datas << id;
            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));

            foreignSocket->write(arrBlock);
        }
        else
        {
            int result = QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");

            qDebug () << "\nresult: " << result;
            qDebug() << datas;

            if(result == 1024)
            {
                //foreignSocket->write(arrBlock);
                qDebug() << "\nWrong input!";
                return ;
            }
        }
    }
    else if (recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString() == "amount_of_work")
    {
        QRegularExpression reTime("^[0-9]+$");

        if (reTime.match(datas).hasMatch())
        {
            QByteArray  arrBlock;
            int num = 4;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);

            qDebug() << table_name << col_name << datas << id;
            out << quint16(0) << num << table_name << col_name << datas << id;
            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));

            foreignSocket->write(arrBlock);
        }
        else
        {
            int result = QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");

            qDebug () << "\nresult: " << result;
            qDebug() << datas;

            if(result == 1024)
            {
                //foreignSocket->write(arrBlock);
                qDebug() << "\nWrong input!";
                return ;
            }
        }
    }

    qDebug() << "Data changed \n";
}

void changing::on_pushButton_2_clicked()    //DELETE
{
    QString table_name = ui->comboBox->currentText();
    QString col_name = recievedmodel->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
    int id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();

    qDebug() << "\nId: " << id;
    qDebug() << "\nrow: " << row;
    qDebug() << "col_name: " << col_name;

    QByteArray  arrBlock;
    int num = 8;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);

    out << quint16(0) << num << table_name << col_name << id;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    foreignSocket->write(arrBlock);
}



void changing::on_comboBox_2_currentIndexChanged(int index)
{
    flag1 = 1;

    qDebug() << ui->tableView->model()->data(ui->tableView->currentIndex(), Qt::DisplayRole);

    qDebug() << ui->comboBox_2->count();

    qDebug () << ui->tableView->currentIndex();
    qDebug() << row << column;
    qDebug() << ui->tableView->model()->index(row, column);

    if (flag == 1)
    {
        qDebug() << "\nreturn\n";
        return;
    }
    else if (flag == 0)
    {
        if (recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString() == "group")
        {
            QString group;
            QString table_name = ui->comboBox->currentText();
            int id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();
            int id_group = 0;
            QString col_name = recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
            group = ui->comboBox_2->currentText();
            recievedmodel->setData(ui->tableView->currentIndex(), group);
            qDebug() << "Изменненая группа: " << group;
            qDebug() << "Выбранная таблица: " << table_name;
            qDebug() << "ID: " << id;
            qDebug() << "Название столбца: " << col_name;

            if (!foreignMapChangingGroups.contains(group))
            {
                qDebug() << "Такой группы не существует";
                return ;
            }
            else
            {
                id_group = foreignMapChangingGroups.take(group);
                qDebug() << "id_group" << id_group;
            }

            QString id_groupstr = QString("%0").arg(id_group);
            qDebug() << id_groupstr;

            QByteArray  arrBlock;
            int num = 4;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);

            out << quint16(0) << num << table_name << col_name << id_groupstr << id;
            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));
            foreignSocket->write(arrBlock);
            flag = 1;
        }
        else if (recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString() == "squad")
        {
            QString squad;
            QString table_name = ui->comboBox->currentText();
            int id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();
            int id_squad = 0;
            QString col_name = recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
            recievedmodel->setData(ui->tableView->currentIndex(), ui->comboBox_2->currentText());
            squad = ui->comboBox_2->currentText();
            qDebug() << "Изменненый отряд: " << squad;
            qDebug() << "Выбранная таблица: " << table_name;
            qDebug() << "ID: " << id;
            qDebug() << "Название столбца: " << col_name;

            if (!foreignMapChangingSquads.contains(squad))
            {
                qDebug() << "Такого отряда не существует";
                return ;
            }
            else
            {
                id_squad = foreignMapChangingSquads.take(squad);
                qDebug() << "id_squad" << id_squad;
            }

            QString id_squadstr = QString("%0").arg(id_squad);
            qDebug() << id_squadstr;

            QByteArray  arrBlock;
            int num = 4;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);

            out << quint16(0) << num << table_name << col_name << id_squadstr << id;
            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));
            foreignSocket->write(arrBlock);
            flag = 1;
        }
        else if (recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString() == "address")
        {
            QString address;
            QString table_name = ui->comboBox->currentText();
            int id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();
            int id_address = 0;
            QString col_name = recievedmodel->headerData(column, Qt::Horizontal, Qt::DisplayRole).toString();
            QString col_name_table = recievedmodel->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString();
            recievedmodel->setData(ui->tableView->currentIndex(), ui->comboBox_2->currentText());
            address = ui->comboBox_2->currentText();
            qDebug() << "Изменненый адрес: " << address;
            qDebug() << "Выбранная таблица: " << table_name;
            qDebug() << "ID: " << id;
            qDebug() << "Название столбца: " << col_name;

            if (!foreignMapChangingWork.contains(address))
            {
                qDebug() << "Такого адреса не существует";
                return ;
            }
            else
            {
                id_address = foreignMapChangingWork.take(address);
                qDebug() << "id_address" << id_address;
            }

            QString id_addressstr = QString("%0").arg(id_address);
            qDebug() << id_addressstr;

            QByteArray  arrBlock;
            int num = 4;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);

            out << quint16(0) << num << table_name << col_name << id_addressstr << id;
            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));
            foreignSocket->write(arrBlock);
            flag = 1;
        }
    }

    qDebug() << "\non_comboBox_2_currentIndexChanged flag: " << flag;

    qDebug() << "Значение из Combobox 2";

    flag = 1;
}


void changing::on_pushButton_clicked()      //1000
{
    QByteArray  arrBlock;
    int num = 13;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int student_id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();

    out << quint16(0) << num << student_id << 1000;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    foreignSocket->write(arrBlock);
}


void changing::on_pushButton_3_clicked()        //5000
{
    QByteArray  arrBlock;
    int num = 13;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int student_id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();

    out << quint16(0) << num << student_id << 5000;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    foreignSocket->write(arrBlock);
}


void changing::on_pushButton_4_clicked()        //10000
{
    QByteArray  arrBlock;
    int num = 13;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_4);
    int student_id = recievedmodel->data(recievedmodel->index(row, 0), Qt::DisplayRole).toInt();

    out << quint16(0) << num << student_id << 10000;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    foreignSocket->write(arrBlock);
}

