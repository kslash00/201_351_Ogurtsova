#include "visib.h"
#include "ui_visib.h"

#include <QListWidget>
#include <QListWidgetItem>
#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "addsch.h"
#include "crypt.h"
#include "schet.h"
#include "dbmodel.h"
#include "qaesencryption.h"

visib::visib(QString key, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::visib)
{
    this->key = key; //инициализация поля key класса AccList
    qInfo() << "key in acclist" << this->key;
    DBModel db(this->key); // передаем поле key конструктору класса DBModel
    auto json = db.json;
    for (int i = 0; i < json.size(); ++i) {
        //this->addRow(db.getRow(i)); //добавление строки логин.пароль
    }
}


visib::~visib()
{
    delete ui;
}

/*void visib::addRow(const DBModel::Row row) {  // добавление записей в GUI
    auto item = new QListWidgetItem();
    auto widget = new CustomWidget(key, this);
    widget->setText(row);
    item->setSizeHint(widget->sizeHint());
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, widget);
}*/

void visib::on_pushButton_clicked()
{
    addsch NewWindow; //открывается окно addacc
    NewWindow.setModal(true);
    if (NewWindow.exec() == QDialog::Accepted) {
        auto row = NewWindow.getInputValues();

        DBModel db(this->key); //инициализация поля key в dbmodel
        auto eRow = db.encrypt(row);
       // this->addRow(eRow); //добавление добавленной записи в окно addacc

        db.writeRowToJSON(eRow); //добавление зашифрованной записи в json файл
    }
}

