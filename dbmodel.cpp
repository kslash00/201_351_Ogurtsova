#include "dbmodel.h"
#include <iostream>
#include "QDebug"
#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "crypt.h"

DBModel::DBModel(const QString key) {
    this->key = key;
    this->file = readFile();
    this->json = readJson(key);
}
const QString DBModel::kFileName = "encoded.json";

QJsonArray DBModel::readJson(QString key) { //парсинг json
    auto decodedFile = Crypt::decrypt(this->file, key, key);

    auto start = decodedFile.indexOf("\n");
    auto jsonStr = decodedFile.sliced(start, decodedFile.length() - start);

    QJsonDocument d = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonArray json = d.QJsonDocument::array();
    qDebug() << d;
    return json;
}

QByteArray DBModel::readFile() { //чтение файла
    QFile file(DBModel::kFileName);

    file.open(QIODevice::ReadWrite | QIODevice::Text);
    auto readedFile = file.readAll(); //в readedFile запишется весь прочитанный файл

    file.close();
    return readedFile;
}

void DBModel::writeFile() { //функция записи json структуры в файл
    QJsonDocument doc(this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact)); // json в строку

    QFile file(DBModel::kFileName);
    file.open(QIODevice::ReadWrite | QIODevice::Text);

    auto encodedText = Crypt::encrypt((this->key + "\n" + strJson).toUtf8(),
                                      this->key, this->key);
    file.write(encodedText);

    file.close();
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    this->file = file.readAll(); //обновляем поле file
    file.close();
}

void DBModel::writeRowToJSON(DBModel::Row row) { //при добавлении новой записи
    QJsonObject obj;
    obj[DBModel::fields.Sch] = row.Sch; //запись
    obj[DBModel::fields.Data] = row.Data;
    obj[DBModel::fields.IDSSch] = row.IDSSch;

    this->json.append(obj);
    this->writeFile();
}

void DBModel::deleteRowFromJSON(int index) {
    this->json.removeAt(index);

    this->writeFile();
}

DBModel::Row DBModel::getRow(int index) {
    QJsonObject jsonRow = json[index].toObject();
    DBModel::Row row = {jsonRow["IDSSch"].toString(), jsonRow["Sch"].toString(),
                        jsonRow["Data"].toString()};
    return row;
}

DBModel::Row DBModel::encrypt(DBModel::Row row) {
    auto Sch = row.Sch;
    auto eSch = Crypt::encrypt((Sch).toUtf8(), this->key, this->key);

    auto Data = row.Data;
    auto ePass = Crypt::encrypt((Data).toUtf8(), this->key, this->key);

    Row res = {row.IDSSch, eSch, ePass};
    return res;
}

DBModel::Row DBModel::decrypt(DBModel::Row row) {
    auto Sch = row.Sch;
    auto plainSch = Crypt::decrypt((Sch).toUtf8(), this->key, this->key);

    auto Data = row.Data;
    auto plainData = Crypt::decrypt((Data).toUtf8(), this->key, this->key);

    Row res = {row.IDSSch, plainSch, plainData};
    return res;
}
