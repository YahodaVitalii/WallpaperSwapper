#include "randomimagelist.h"

RandomImageList::RandomImageList() : id(-1) {}

RandomImageList::RandomImageList(QString name,const QDateTime& interval, const QVector<int>& ids)
    : id(-1), name(name),timeInterval(interval), imageIds(ids) {}

QString RandomImageList::getName() const
{
    return name;
}

void RandomImageList::setName(QString name)
{
    this->name = name;
}

// Геттери та сеттери
int RandomImageList::getId() const { return id; }

void RandomImageList::setId(int newId) { id = newId; }

QDateTime RandomImageList::getTimeInterval() const { return timeInterval; }

void RandomImageList::setTimeInterval(const QDateTime& newTimeInterval) { timeInterval = newTimeInterval; }

QVector<int> RandomImageList::getImageIds() const { return imageIds; }

void RandomImageList::setImageIds(const QVector<int>& newImageIds) { imageIds = newImageIds; }

// Методи серіалізації та десеріалізації у формат JSON
QString RandomImageList::toJsonString() const {
    QJsonArray jsonArray;
    for (int id : imageIds) {
        jsonArray.append(id);
    }

    QJsonObject jsonObj;
    jsonObj["images"] = jsonArray;

    QJsonDocument jsonDoc(jsonObj);
    return QString(jsonDoc.toJson(QJsonDocument::Compact));
}

void RandomImageList::fromJsonString(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    QVector<int> imageIds;
    QJsonArray jsonArray = jsonObj["images"].toArray();
    for (const QJsonValue& value : jsonArray) {
        imageIds.append(value.toInt());
    }

   this->imageIds=imageIds;
}
