#include "schet.h"
#include "ui_schet.h"

Schet::Schet(QString key, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Schet)
{
    ui->setupUi(this);
}

Schet::~Schet()
{
    delete ui;
}
