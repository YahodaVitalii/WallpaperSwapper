#ifndef WEEKIMAGELIST_H
#define WEEKIMAGELIST_H


#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "baseimagelist.h"


class WeekImageList : public BaseImageList {
public:
    QMap<QString, int> images;

    // Конструктори
    WeekImageList();
    WeekImageList(QString name, const QMap<QString, int>& images);

    // Геттери та сеттери
    QMap<QString, int> getImages() const;
    void setImages(const QMap<QString, int>& newImages);

    // Методи серіалізації та десеріалізації у формат JSON
    QString toJsonString() const override;
    void fromJsonString(const QString& jsonString) override;
};

#endif // WEEKIMAGELIST_H
