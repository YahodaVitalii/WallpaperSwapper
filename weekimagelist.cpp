#include "weekimagelist.h"

WeekImageList::WeekImageList() : BaseImageList() {}

WeekImageList::WeekImageList(QString name, const QMap<QString, int>& images)
    : BaseImageList(name), images(images) {}

QMap<QString, int> WeekImageList::getImages() const {
    return images;
}

void WeekImageList::setImages(const QMap<QString, int>& newImages) {
    images = newImages;
}

QString WeekImageList::toJsonString() const {
    QJsonObject jsonObj;
    for (auto it = images.begin(); it != images.end(); ++it) {
        jsonObj[it.key()] = it.value();
    }

    QJsonObject rootObj;
    rootObj["name"] = name;  // Поле name успадковане з BaseImageList
    rootObj["images"] = jsonObj;

    QJsonDocument jsonDoc(rootObj);
    return QString(jsonDoc.toJson(QJsonDocument::Compact));
}

void WeekImageList::fromJsonString(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject rootObj = jsonDoc.object();

    name = rootObj["name"].toString();  // Поле name успадковане з BaseImageList

    QJsonObject jsonObj = rootObj["images"].toObject();
    QMap<QString, int> images;
    for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        images[it.key()] = it.value().toInt();
    }

    this->images = images;
}
