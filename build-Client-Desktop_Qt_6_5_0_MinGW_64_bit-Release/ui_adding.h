/********************************************************************************
** Form generated from reading UI file 'adding.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDING_H
#define UI_ADDING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adding
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QComboBox *comboBox_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QLabel *label_6;

    void setupUi(QWidget *adding)
    {
        if (adding->objectName().isEmpty())
            adding->setObjectName("adding");
        adding->setEnabled(true);
        adding->resize(750, 546);
        adding->setMinimumSize(QSize(750, 546));
        adding->setMaximumSize(QSize(750, 546));
        layoutWidget = new QWidget(adding);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(600, 210, 82, 56));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout_2->addWidget(pushButton_2);

        layoutWidget1 = new QWidget(adding);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(150, 170, 411, 176));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget1);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(layoutWidget1);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(layoutWidget1);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(layoutWidget1);
        lineEdit_4->setObjectName("lineEdit_4");

        verticalLayout->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(layoutWidget1);
        lineEdit_5->setObjectName("lineEdit_5");

        verticalLayout->addWidget(lineEdit_5);

        comboBox_2 = new QComboBox(adding);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setGeometry(QRect(30, 40, 131, 24));
        layoutWidget2 = new QWidget(adding);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(12, 170, 131, 171));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName("label");

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName("label_3");
        label_3->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_3->addWidget(label_3);

        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");

        verticalLayout_3->addWidget(label_4);

        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        layoutWidget3 = new QWidget(adding);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(150, 380, 561, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(layoutWidget3);
        comboBox->setObjectName("comboBox");

        horizontalLayout->addWidget(comboBox);

        comboBox_3 = new QComboBox(layoutWidget3);
        comboBox_3->setObjectName("comboBox_3");

        horizontalLayout->addWidget(comboBox_3);

        comboBox_4 = new QComboBox(layoutWidget3);
        comboBox_4->setObjectName("comboBox_4");

        horizontalLayout->addWidget(comboBox_4);

        comboBox_5 = new QComboBox(layoutWidget3);
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->addItem(QString());
        comboBox_5->setObjectName("comboBox_5");

        horizontalLayout->addWidget(comboBox_5);

        label_6 = new QLabel(adding);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(180, 140, 49, 16));

        retranslateUi(adding);

        QMetaObject::connectSlotsByName(adding);
    } // setupUi

    void retranslateUi(QWidget *adding)
    {
        adding->setWindowTitle(QCoreApplication::translate("adding", "\320\230\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\265", nullptr));
        pushButton->setText(QCoreApplication::translate("adding", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("adding", "PushButton", nullptr));
        label->setText(QCoreApplication::translate("adding", "\320\244\320\260\320\274\320\270\320\273\320\270\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("adding", "\320\230\320\274\321\217", nullptr));
        label_3->setText(QCoreApplication::translate("adding", "\320\236\321\202\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        label_4->setText(QCoreApplication::translate("adding", "\320\240\320\260\320\261\320\276\321\202\320\260 \320\262 \320\275\320\276\321\200\320\274\320\276-\321\207\320\260\321\201\320\260\321\205", nullptr));
        label_5->setText(QCoreApplication::translate("adding", "\320\227\320\260\321\200\320\277\320\273\320\260\321\202\320\260", nullptr));
        comboBox_5->setItemText(0, QCoreApplication::translate("adding", "1 \320\272\321\203\321\200\321\201", nullptr));
        comboBox_5->setItemText(1, QCoreApplication::translate("adding", "2 \320\272\321\203\321\200\321\201", nullptr));
        comboBox_5->setItemText(2, QCoreApplication::translate("adding", "3 \320\272\321\203\321\200\321\201", nullptr));
        comboBox_5->setItemText(3, QCoreApplication::translate("adding", "4 \320\272\321\203\321\200\321\201", nullptr));

        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class adding: public Ui_adding {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDING_H
