#include "dayimagelist.h"

DayImageList::DayImageList() : BaseImageList() {}

DayImageList::DayImageList(QString name, const QVector<TimeRangeImage>& images)
    : BaseImageList(name), images(images) {}

QVector<TimeRangeImage> DayImageList::getImages() const {
    return images;
}

void DayImageList::setImages(const QVector<TimeRangeImage>& newImages) {
    images = newImages;
}

QString DayImageList::toJsonString() const {
    QJsonArray jsonArray;
    for (const auto& timeRangeImage : images) {
        QJsonObject jsonTimeRangeImage;
        jsonTimeRangeImage["startTime"] = timeRangeImage.startTime;
        jsonTimeRangeImage["endTime"] = timeRangeImage.endTime;
        jsonTimeRangeImage["imageId"] = timeRangeImage.imageId;
        jsonTimeRangeImage["id"] = timeRangeImage.id;
        jsonArray.append(jsonTimeRangeImage);
    }

    QJsonObject jsonObj;
    jsonObj["name"] = name;  // Поле name успадковане з BaseImageList
    jsonObj["images"] = jsonArray;

    QJsonDocument jsonDoc(jsonObj);
    return QString(jsonDoc.toJson(QJsonDocument::Compact));
}

void DayImageList::fromJsonString(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    name = jsonObj["name"].toString();  // Поле name успадковане з BaseImageList

    QJsonArray jsonArray = jsonObj["images"].toArray();
    images.clear();
    for (const auto& jsonValue : jsonArray) {
        QJsonObject jsonTimeRangeImage = jsonValue.toObject();
        TimeRangeImage timeRangeImage(
            jsonTimeRangeImage["startTime"].toString(),
            jsonTimeRangeImage["endTime"].toString(),
            jsonTimeRangeImage["imageId"].toInt(),
            jsonTimeRangeImage["id"].toInt()
        );
        images.append(timeRangeImage);
    }
}
