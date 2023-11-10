#ifndef DBMODEL_H
#define DBMODEL_H

#include "QDebug"
#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "QString"

class DBModel
{
public:
    DBModel();
        DBModel(const QString key);
        QString key;
        QByteArray file;
        QJsonArray json;

        static const QString kFileName;
        const struct {
            QString IDSSch;
            QString Sch;
            QString Data;
        } fields = {"IDSSch", "Sch", "Data"};

        struct Row {
            QString IDSSch;
            QString Sch;
            QString Data;
        };

        QJsonArray readJson(QString key);

        static QByteArray readFile();
        void writeFile();
        void writeRowToJSON(Row row);

        Row getRow(int index);

        Row encrypt(Row row);
        Row decrypt(Row row);
        void deleteRowFromJSON(int index);
};

#endif // DBMODEL_H
