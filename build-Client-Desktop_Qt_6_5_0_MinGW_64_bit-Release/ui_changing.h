/********************************************************************************
** Form generated from reading UI file 'changing.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGING_H
#define UI_CHANGING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_changing
{
public:
    QHBoxLayout *horizontalLayout;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;

    void setupUi(QWidget *changing)
    {
        if (changing->objectName().isEmpty())
            changing->setObjectName("changing");
        changing->resize(898, 499);
        horizontalLayout = new QHBoxLayout(changing);
        horizontalLayout->setObjectName("horizontalLayout");
        tableView = new QTableView(changing);
        tableView->setObjectName("tableView");

        horizontalLayout->addWidget(tableView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        pushButton = new QPushButton(changing);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_3 = new QPushButton(changing);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(changing);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout->addWidget(pushButton_4);

        pushButton_2 = new QPushButton(changing);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        comboBox = new QComboBox(changing);
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        comboBox_2 = new QComboBox(changing);
        comboBox_2->setObjectName("comboBox_2");

        verticalLayout->addWidget(comboBox_2);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(changing);

        QMetaObject::connectSlotsByName(changing);
    } // setupUi

    void retranslateUi(QWidget *changing)
    {
        changing->setWindowTitle(QCoreApplication::translate("changing", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("changing", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\321\202\321\214 \320\262\321\213\320\277\320\273\320\260\321\202\321\213\n"
"\320\275\320\260 1000", nullptr));
        pushButton_3->setText(QCoreApplication::translate("changing", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\321\202\321\214 \320\262\321\213\320\277\320\273\320\260\321\202\321\213\n"
"\320\275\320\260 5000", nullptr));
        pushButton_4->setText(QCoreApplication::translate("changing", "\320\243\320\262\320\265\320\273\320\270\321\207\320\270\321\202\321\214 \320\262\321\213\320\277\320\273\320\260\321\202\321\213\n"
"\320\275\320\260 10000", nullptr));
        pushButton_2->setText(QCoreApplication::translate("changing", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class changing: public Ui_changing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGING_H
