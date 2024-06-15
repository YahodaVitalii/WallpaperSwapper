#include "dayimagelist.h"

DayImageList::DayImageList() : id(-1) {}

DayImageList::DayImageList(QString name, const QVector<TimeRangeImage>& images)
    : id(-1), name(name), images(images) {}

QString DayImageList::getName() const {
    return name;
}

void DayImageList::setName(const QString& name) {
    this->name = name;
}

int DayImageList::getId() const { return id; }

void DayImageList::setId(int newId) { id = newId; }

QVector<TimeRangeImage> DayImageList::getImages() const { return images; }

void DayImageList::setImages(const QVector<TimeRangeImage>& newImages) { images = newImages; }

QString DayImageList::toJsonString() const {
    QJsonArray jsonArray;
    for (const auto& timeRangeImage : images) {
        QJsonObject jsonTimeRangeImage;
        jsonTimeRangeImage["startTime"] = timeRangeImage.startTime;
        jsonTimeRangeImage["endTime"] = timeRangeImage.endTime;
        jsonTimeRangeImage["imageId"] = timeRangeImage.imageId;
        jsonArray.append(jsonTimeRangeImage);
    }

    QJsonObject jsonObj;
    jsonObj["name"] = name;
    jsonObj["images"] = jsonArray;

    QJsonDocument jsonDoc(jsonObj);
    return QString(jsonDoc.toJson(QJsonDocument::Compact));
}

void DayImageList::fromJsonString(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    name = jsonObj["name"].toString();

    QJsonArray jsonArray = jsonObj["images"].toArray();
    images.clear();
    for (const auto& jsonValue : jsonArray) {
        QJsonObject jsonTimeRangeImage = jsonValue.toObject();
        TimeRangeImage timeRangeImage(
            jsonTimeRangeImage["startTime"].toString(),
            jsonTimeRangeImage["endTime"].toString(),
            jsonTimeRangeImage["imageId"].toInt()
        );
        images.append(timeRangeImage);
    }
}
