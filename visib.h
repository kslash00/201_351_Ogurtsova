#ifndef VISIB_H
#define VISIB_H

#include <QDialog>
#include <QDialog>
#include "dbmodel.h"

namespace Ui {
class visib;
}

class visib : public QDialog
{
    Q_OBJECT

public:
    explicit visib(QString key, QWidget *parent = nullptr);
    ~visib();
    QString key;
   // void addRow(const DBModel::Row row);

private slots:
    //void addRow(const DBModel::Row row);
    void on_pushButton_clicked();

private:
    Ui::visib *ui;
};

#endif // VISIB_H
