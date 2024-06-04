#include "weekimagelist.h"

WeekImageList::WeekImageList() : id(-1) {}

WeekImageList::WeekImageList(QString name, const QMap<QString, int>& images)
    : id(-1), name(name), images(images) {}

QString WeekImageList::getName() const {
    return name;
}

void WeekImageList::setName(const QString& name) {
    this->name = name;
}

int WeekImageList::getId() const { return id; }

void WeekImageList::setId(int newId) { id = newId; }

QMap<QString, int> WeekImageList::getImages() const { return images; }

void WeekImageList::setImages(const QMap<QString, int>& newImages) { images = newImages; }

// Методи серіалізації та десеріалізації у формат JSON
QString WeekImageList::toJsonString() const {
    QJsonObject jsonObj;
    for (auto it = images.begin(); it != images.end(); ++it) {
        jsonObj[it.key()] = it.value();
    }

    QJsonDocument jsonDoc(jsonObj);
    return QString(jsonDoc.toJson(QJsonDocument::Compact));
}

void WeekImageList::fromJsonString(const QString& jsonString) {
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject jsonObj = jsonDoc.object();

    QMap<QString, int> images;
    for (auto it = jsonObj.begin(); it != jsonObj.end(); ++it) {
        images[it.key()] = it.value().toInt();
    }

    this->images = images;
}
