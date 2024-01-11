#include "adding.h"
#include "ui_adding.h"
#include <QStandardItem>
#include <QRegularExpression>
#include <QMessageBox>


adding::adding(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adding)
{
    ui->setupUi(this);
}

adding::~adding()
{
    delete ui;
}

void adding::showTable(QStandardItemModel *model)
{

    //ui->tableView->setModel(model);
}

void adding::TcpSocket(QTcpSocket *socket)
{
    foreignSocket = socket;
    qDebug() << "Socket from \'adding\': " << foreignSocket;

    //connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(on_comboBox1_currentIndexChanged(int)));
}

void adding::on_comboBox_2_currentIndexChanged(int index)
{
    if (ui->comboBox_2->itemText(index) == "work_place")
    {
        ui->label->setText("Тип работ");
        ui->label_2->setText("Адрес");
        ui->label->show();
        ui->label_2->show();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->comboBox->hide();
        ui->comboBox_3->hide();
        ui->comboBox_4->hide();
        ui->comboBox_5->hide();
    }
    else if (ui->comboBox_2->itemText(index) == "students")
    {
        ui->label->setText("Фамилия");
        ui->label_2->setText("Имя");
        ui->label_3->setText("Отчество");
        ui->label_4->setText("Работа в нормо-часах");
        ui->label_5->setText("Зарплата");

        ui->label->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->label_5->show();

        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        ui->lineEdit_5->show();

        ui->comboBox->show();
        ui->comboBox_3->show();
        ui->comboBox_4->show();
        ui->comboBox_5->show();
    }
    else if (ui->comboBox_2->itemText(index) == "stud_groups")
    {
        ui->comboBox->hide();
        ui->comboBox_3->hide();
        ui->comboBox_4->hide();
        ui->comboBox_5->hide();

        ui->label->setText("Новая группа");
        ui->label->show();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->lineEdit->show();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();
    }
    else if (ui->comboBox_2->itemText(index) == "squads")
    {
        ui->label->setText("Добавить стройотряд");

        ui->label->show();
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->label_5->hide();

        ui->lineEdit->show();
        ui->lineEdit_2->hide();
        ui->lineEdit_3->hide();
        ui->lineEdit_4->hide();
        ui->lineEdit_5->hide();

        ui->comboBox->hide();
        ui->comboBox_3->hide();
        ui->comboBox_4->hide();
        ui->comboBox_5->hide();
    }
}


bool onlyRussianLettersAdding(QString text)
{
    static QRegularExpression russianAlphabet("^[А-Яа-я]+$");
    return russianAlphabet.match(text).hasMatch();
}

void adding::on_pushButton_clicked()        //ADD
{
    QString lastname;
    QString name;
    QString middlename;
    QString curs;
    QString group;
    QString squad;
    QString type_of_construction;
    QString address;
    QString amount_of_work;
    QString salaryString;
    float salary;
    QString newGroup;
    QString newSquad;
    QString table_name = ui->comboBox_2->currentText();
    int num = 2;
    qDebug() << "\n";

    bool onlyRussianLettersAdding(QString text);

    if (ui->comboBox_2->currentText() == "work_place")
    {
        type_of_construction = ui->lineEdit->text();
        address = ui->lineEdit_2->text();

        QRegularExpression regExp("[а-яА-ЯёЁ\\s\\p{P}]*");

        if (regExp.match(address).hasMatch() && onlyRussianLettersAdding(type_of_construction))
        {
            QByteArray  arrBlock;
            QDataStream out(&arrBlock, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_6_4);
            out << quint16(0) << num << table_name << type_of_construction << address;

            out.device()->seek(0);
            out << quint16(arrBlock.size() - sizeof(quint16));

            qDebug() << "adding: " << arrBlock;
            qDebug() << "adding size: " << arrBlock.size();

            foreignSocket->write(arrBlock);

            qDebug() << "type_ofconstruction " << type_of_construction;
            qDebug() << "address " << address;
        }
        else
        {
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui->lineEdit_5->setText("");

            QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");
            return ;
        }
    }
    else if (ui->comboBox_2->currentText() == "students")
    {
        lastname = ui->lineEdit->text();
        name = ui->lineEdit_2->text();
        middlename = ui->lineEdit_3->text();
        curs = ui->comboBox_5->currentText();
        group = ui->comboBox->currentText();
        amount_of_work = ui->lineEdit_4->text();
        salaryString = ui->lineEdit_5->text();
        salaryString.replace(',', '.');
        salary = salaryString.toFloat();
        salary = ceil(salary * 100) / 100;
        squad = ui->comboBox_3->currentText();
        address = ui->comboBox_4->currentText();

        qDebug() << "salary: " << salary;

        QRegularExpression reTime("^[0-9]+$");


        if (reTime.match(amount_of_work).hasMatch())
        {
            qDebug() << "Часы введены корректно\n";
        }
        else
        {
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui->lineEdit_5->setText("");

            QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");

            //qDebug() << "Ошибка ввода часов!";
            return;
        }

        if (salary > 0)
        {
            qDebug() << "salary is correct!";
        }
        else
        {
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui->lineEdit_5->setText("");

            QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");

            //qDebug() << "Ошибка ввода часов!";

            qDebug() << "Введено число не типа float";
            return;
        }

        //amount_of_work = amount_of_work + " нормо-часов";

        if (!onlyRussianLettersAdding(lastname) || !onlyRussianLettersAdding(name) || !onlyRussianLettersAdding(middlename))
        {
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui->lineEdit_5->setText("");

            QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");
            qDebug() << "Неправильное ФИО";
            return ;
        }

        int num = 2;

        qDebug() << "\nGroup:" << group;

        int id_group = NULL;
        int id_squad = NULL;
        int id_place = NULL;

        if (!foreignMapAddingGroups.contains(group))
        {
            qDebug() << "Такой группы не существует";
            return ;
        }
        else
        {
            id_group = foreignMapAddingGroups.take(group);
            qDebug() << "id_group" << id_group;
        }

        if (!foreignMapAddingSquads.contains(squad))
        {
            qDebug() << "Такого отряда не существует";
            return ;
        }
        else
        {
            id_squad = foreignMapAddingSquads.take(squad);
            qDebug() << "id_squad" << id_squad;
        }

        if (!foreignMapAddingWork.contains(address))
        {
            qDebug() << "Такого адреса не существует";
            return ;
        }
        else
        {
            id_place = foreignMapAddingWork.take(address);
            qDebug() << "id_work" << id_place;
        }

        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_4);
        out << quint16(0) << num << table_name << lastname << name << middlename << curs << id_group << id_squad << id_place << amount_of_work << salary;

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        qDebug() << "adding: " << arrBlock;
        qDebug() << "adding size: " << arrBlock.size();

        foreignSocket->write(arrBlock);


        qDebug() << lastname;
        qDebug() << name;
        qDebug() << middlename;
        qDebug() << group;
        qDebug() << amount_of_work;
        qDebug() << salary;
    }
    else if (ui->comboBox_2->currentText() == "stud_groups")
    {
        newGroup = ui->lineEdit->text();

        QRegularExpression reGroup("^[А-Я]{4}-[0-9]{2}-[0-9]{2}$");

        if (reGroup.match(newGroup).hasMatch())
        {
            qDebug() << "\nГруппа введа корректно";
        }
        else
        {
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui->lineEdit_5->setText("");

            QMessageBox::warning(0, "Ошибка ввода", "Группа введена не по шаблону\nПример: БСБО-00-00");
            qDebug() << "\nГруппа введа неправильно";
            return;
        }

        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_4);
        out << quint16(0) << num << table_name << newGroup;

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        qDebug() << "adding: " << arrBlock;
        qDebug() << "adding size: " << arrBlock.size();

        foreignSocket->write(arrBlock);

        qDebug() << newGroup;
    }
    else if (ui->comboBox_2->currentText() == "squads")
    {
        newSquad = ui->lineEdit->text();

        if (!onlyRussianLettersAdding(newSquad))
        {
            ui->lineEdit->setText("");
            ui->lineEdit_2->setText("");
            ui->lineEdit_3->setText("");
            ui->lineEdit_4->setText("");
            ui->lineEdit_5->setText("");

            QMessageBox::warning(0, "Ошибка ввода", "Неправильный(-ые) символ(-ы)");
            qDebug() << "\nОтряд введен неправильно";
            return;
        }

        QByteArray  arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_6_4);
        out << quint16(0) << num << table_name << newSquad;

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        qDebug() << "adding: " << arrBlock;
        qDebug() << "adding size: " << arrBlock.size();

        foreignSocket->write(arrBlock);

        qDebug() << newSquad;
    }

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
}

