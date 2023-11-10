#ifndef SCHET_H
#define SCHET_H

#include <QDialog>

namespace Ui {
class Schet;
}

class Schet : public QDialog
{
    Q_OBJECT

public:
    explicit Schet(QString key, QWidget *parent = nullptr);
    ~Schet();
    bool show = false;
    QString key;



private:
    Ui::Schet *ui;
};

#endif // SCHET_H
