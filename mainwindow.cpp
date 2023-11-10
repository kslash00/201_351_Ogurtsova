#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "schet.h"

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
    if (pinCode == "1234"){
        Schet NewWindow(pinCode); //если верно - открывается следующее окно
        NewWindow.setModal(true);
        NewWindow.exec();
    } else {
        QMessageBox::warning(this, "Authotization", "Invalid PIN code"); //если неверно - вывод соответствующего сообщения
    }
}

