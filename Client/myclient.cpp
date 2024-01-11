#include "myclient.h"
#include "ui_myclient.h"

myclient::myclient(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::myclient)
{
    ui->setupUi(this);
}

myclient::~myclient()
{
    delete ui;
}

void myclient::on_pushButton_clicked()
{

}

