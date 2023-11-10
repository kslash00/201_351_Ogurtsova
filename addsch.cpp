#include "addsch.h"
#include "ui_addsch.h"
#include "dbmodel.h"

addsch::addsch(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addsch)
{
    ui->setupUi(this);
}

addsch::~addsch() { delete ui; }
DBModel::Row addsch::getInputValues() const { //функция берет значения из окна addacc
    QString Url = ui->inputIDSSch->text();
    QString Login = ui->inputSch->text();
    QString Pass = ui->inputData->text();
    DBModel::Row row = {Url, Login, Pass}; //создается поле row в dbmodel

    return row;
}

void addsch::on_pushButton_clicked()
{
    //DBModel::Row addsch::getInputValues() const;
}

