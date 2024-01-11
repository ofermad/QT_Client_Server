/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTableView *tableView;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_6;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label;
    QPushButton *pushButton_5;
    QComboBox *comboBox_4;
    QLineEdit *lineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1067, 612);
        MainWindow->setMinimumSize(QSize(1067, 612));
        MainWindow->setMaximumSize(QSize(1067, 612));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(380, 10, 251, 71));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(380, 90, 681, 471));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        tableView = new QTableView(verticalLayoutWidget);
        tableView->setObjectName("tableView");

        verticalLayout_2->addWidget(tableView);

        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(9, 9, 361, 551));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox = new QComboBox(layoutWidget);
        comboBox->setObjectName("comboBox");

        verticalLayout->addWidget(comboBox);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName("pushButton_2");

        verticalLayout->addWidget(pushButton_2);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName("pushButton");

        verticalLayout->addWidget(pushButton);

        pushButton_8 = new QPushButton(layoutWidget);
        pushButton_8->setObjectName("pushButton_8");

        verticalLayout->addWidget(pushButton_8);

        pushButton_7 = new QPushButton(layoutWidget);
        pushButton_7->setObjectName("pushButton_7");

        verticalLayout->addWidget(pushButton_7);

        pushButton_9 = new QPushButton(layoutWidget);
        pushButton_9->setObjectName("pushButton_9");

        verticalLayout->addWidget(pushButton_9);

        pushButton_10 = new QPushButton(layoutWidget);
        pushButton_10->setObjectName("pushButton_10");

        verticalLayout->addWidget(pushButton_10);

        pushButton_11 = new QPushButton(layoutWidget);
        pushButton_11->setObjectName("pushButton_11");

        verticalLayout->addWidget(pushButton_11);

        pushButton_12 = new QPushButton(layoutWidget);
        pushButton_12->setObjectName("pushButton_12");

        verticalLayout->addWidget(pushButton_12);

        pushButton_13 = new QPushButton(layoutWidget);
        pushButton_13->setObjectName("pushButton_13");

        verticalLayout->addWidget(pushButton_13);

        pushButton_14 = new QPushButton(layoutWidget);
        pushButton_14->setObjectName("pushButton_14");

        verticalLayout->addWidget(pushButton_14);

        pushButton_6 = new QPushButton(layoutWidget);
        pushButton_6->setObjectName("pushButton_6");

        verticalLayout->addWidget(pushButton_6);

        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName("pushButton_3");

        verticalLayout->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(layoutWidget);
        pushButton_4->setObjectName("pushButton_4");

        verticalLayout->addWidget(pushButton_4);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(750, 10, 231, 16));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(830, 60, 80, 24));
        comboBox_4 = new QComboBox(centralwidget);
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->addItem(QString());
        comboBox_4->setObjectName("comboBox_4");
        comboBox_4->setGeometry(QRect(640, 60, 101, 24));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(760, 60, 113, 24));
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(720, 30, 291, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox_2 = new QComboBox(layoutWidget1);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");

        horizontalLayout->addWidget(comboBox_2);

        comboBox_3 = new QComboBox(layoutWidget1);
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName("comboBox_3");

        horizontalLayout->addWidget(comboBox_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1067, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Connect to Server", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\n"
"\321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\276\320\262 \320\262 \320\263\321\200\321\203\320\277\320\277\320\260\321\205", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\320\241\321\200\320\265\320\264\320\275\321\217\321\217 \320\267\320\260\321\200\320\277\320\273\320\260\321\202\320\260 \n"
"\320\264\320\273\321\217 \320\272\320\260\320\266\320\264\320\276\320\271 \320\263\321\200\321\203\320\277\320\277\321\213", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\320\232\321\202\320\276 \320\272\320\265\320\274 \321\200\320\260\320\261\320\276\321\202\320\260\320\265\321\202", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "\320\232\321\202\320\276 \320\263\320\264\320\265 \321\200\320\260\320\261\320\276\321\202\320\260\320\265\321\202", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\321\203\320\264\320\265\320\275\321\202\321\213 \320\270\320\267 \320\263\321\200\321\203\320\277\320\277,\n"
"\320\263\320\264\320\265 \320\261\320\276\320\273\321\214\321\210\320\265 \320\276\320\264\320\275\320\276\320\263\320\276 \321\207\320\265\320\273\320\276\320\262\320\265\320\272\320\260", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "\320\241\321\200\320\265\320\264\320\275\320\265\320\265 \320\262\321\200\320\265\320\274\321\217 \321\200\320\260\320\261\320\276\321\202\321\213 \320\275\320\260 \320\276\320\261\321\212\320\265\320\272\321\202\320\265", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "\320\241\321\200\320\265\320\264\320\275\321\217\321\217 \320\267\320\260\321\200\320\277\320\273\320\260\321\202\320\260 \321\201\321\202\321\200\320\276\320\271\320\276\321\202\321\200\321\217\320\264\320\260", nullptr));
        pushButton_14->setText(QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\321\213, \320\262 \320\272\320\276\321\202\320\276\321\200\321\213\321\205 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\321\213 \320\276\321\202\321\200\320\260\320\261\320\276\321\202\320\260\320\273\320\270 \320\275\320\276\321\200\320\274\321\203", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270 \321\201\321\202\321\203\320\264\320\265\320\275\321\202\320\276\320\262 \320\270\320\267 \320\262\321\213\320\261\321\200\320\260\320\275\320\275\320\276\320\271 \320\263\321\200\321\203\320\277\320\277\321\213", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        comboBox_4->setItemText(0, QCoreApplication::translate("MainWindow", "\320\221\320\265\320\267 \321\204\320\270\320\273\321\214\321\202\321\200\320\260", nullptr));
        comboBox_4->setItemText(1, QCoreApplication::translate("MainWindow", ">", nullptr));
        comboBox_4->setItemText(2, QCoreApplication::translate("MainWindow", "<", nullptr));
        comboBox_4->setItemText(3, QCoreApplication::translate("MainWindow", ">=", nullptr));
        comboBox_4->setItemText(4, QCoreApplication::translate("MainWindow", "<=", nullptr));
        comboBox_4->setItemText(5, QCoreApplication::translate("MainWindow", "=", nullptr));

        comboBox_2->setItemText(0, QCoreApplication::translate("MainWindow", "\320\223\321\200\321\203\320\277\320\277\320\260 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275\320\260", nullptr));

        comboBox_3->setItemText(0, QCoreApplication::translate("MainWindow", "\320\236\321\202\321\200\321\217\320\264 \320\275\320\265 \320\262\321\213\320\261\321\200\320\260\320\275", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
