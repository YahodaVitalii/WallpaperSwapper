#include "randomimagelist.h"

RandomImageList::RandomImageList() : BaseImageList() {}

RandomImageList::RandomImageList(QString name, const QDateTime& interval, const QVector<int>& ids)
    : BaseImageList(name), timeInterval(interval), imageIds(ids) {}

QDateTime RandomImageList::getTimeInterval() const {
    return timeInterval;
}

void RandomImageList::setTimeInterval(const QDateTime& newTimeInterval) {
    timeInterval = newTimeInterval;
}

QVector<int> RandomImageList::getImageIds() const {
    return imageIds;
}

void RandomImageList::setImageIds(const QVector<int>& newImageIds) {
    imageIds = newImageIds;
}

QString RandomImageList::toJsonString() const {
    QJsonArray jsonArray;
    for (int id : imageIds) {
        jsonArray.append(id);
    }

    QJsonObject jsonObj;
    jsonObj["name"] = name;  // Поле name успадковане з BaseImageList
    jsonObj["timeInterval"] = timeInterval.toString(Qt::ISODate);
    jsonObj["images"] = jsonArray;

    QJsonDocument jsonDoc(jsonObj);
    return QString(jsonDoc.toJson(QJsonDocument::Compact));
}

void RandomImageList::fromJsonString(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    name = jsonObj["name"].toString();  // Поле name успадковане з BaseImageList
    timeInterval = QDateTime::fromString(jsonObj["timeInterval"].toString(), Qt::ISODate);

    QVector<int> imageIds;
    QJsonArray jsonArray = jsonObj["images"].toArray();
    for (const QJsonValue& value : jsonArray) {
        imageIds.append(value.toInt());
    }

    this->imageIds = imageIds;
}
