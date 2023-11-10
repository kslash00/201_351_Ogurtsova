#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "schet.h"

#include "QCryptographicHash"
#include "QFile"
#include "QMessageBox"
#include "QString"
#include "crypt.h"
#include "dbmodel.h"
#include "qaesencryption.h"
#include "QMessageBox"
#include "QString"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString pinCode = ui->pin->text();

    QFile file(DBModel::kFileName);

    if (!file.exists()) {  //проверка существования файла (если сущ - возвращает true и выполняем код, иначе не выполняем
        auto encodedPin =
            Crypt::encrypt((pinCode + "\n[]").toUtf8(), pinCode, pinCode);

        file.open(QIODevice::ReadWrite | QIODevice::Text);
        file.write(encodedPin);
        file.close();

        QMessageBox::warning(this, "Pin", "A new PIN code has been created");
        return MainWindow::on_pushButton_clicked();
    }

    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QByteArray readedText = file.readAll();
    file.close();

    QString decodedText = Crypt::decrypt(readedText, pinCode, pinCode);
    QString decodedKey = decodedText.split("\n")[0];

    qInfo() << "Key" << decodedKey;

    if (decodedKey == pinCode) {
        Schet NewWindow(pinCode);
        NewWindow.setModal(true);
        NewWindow.exec();
    } else {
        QMessageBox::warning(this, "Authotization", "Invalid PIN code");
    }

    /*if (pinCode == "1234"){
        Schet NewWindow(pinCode); //если верно - открывается следующее окно
        NewWindow.setModal(true);
        NewWindow.exec();
    } else {
        QMessageBox::warning(this, "Authotization", "Invalid PIN code"); //если неверно - вывод соответствующего сообщения
    }*/


}

