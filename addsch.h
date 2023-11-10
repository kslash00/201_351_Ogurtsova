#ifndef ADDSCH_H
#define ADDSCH_H

#include <QDialog>
#include "QAbstractButton"
#include "dbmodel.h"

namespace Ui {
class addsch;
}

class addsch : public QDialog
{
    Q_OBJECT

public:
    explicit addsch(QWidget *parent = nullptr);
    ~addsch();
    DBModel::Row getInputValues() const;

private slots:
    void on_pushButton_clicked();

private:
    Ui::addsch *ui;
};

#endif // ADDSCH_H
