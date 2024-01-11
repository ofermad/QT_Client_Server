/********************************************************************************
** Form generated from reading UI file 'authorization.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHORIZATION_H
#define UI_AUTHORIZATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_authorization
{
public:
    QPushButton *pushButton;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *authorization)
    {
        if (authorization->objectName().isEmpty())
            authorization->setObjectName("authorization");
        authorization->resize(400, 400);
        authorization->setMinimumSize(QSize(400, 400));
        authorization->setMaximumSize(QSize(400, 400));
        pushButton = new QPushButton(authorization);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(165, 210, 80, 24));
        label = new QLabel(authorization);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 85, 49, 16));
        label_2 = new QLabel(authorization);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 158, 49, 16));
        lineEdit = new QLineEdit(authorization);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(120, 80, 181, 24));
        lineEdit_2 = new QLineEdit(authorization);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(120, 150, 181, 24));

        retranslateUi(authorization);

        QMetaObject::connectSlotsByName(authorization);
    } // setupUi

    void retranslateUi(QWidget *authorization)
    {
        authorization->setWindowTitle(QCoreApplication::translate("authorization", "Authorization", nullptr));
        pushButton->setText(QCoreApplication::translate("authorization", "Log in", nullptr));
        label->setText(QCoreApplication::translate("authorization", "\320\233\320\276\320\263\320\270\320\275", nullptr));
        label_2->setText(QCoreApplication::translate("authorization", "\320\237\320\260\321\200\320\276\320\273\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class authorization: public Ui_authorization {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHORIZATION_H
