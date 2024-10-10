#ifndef WEEKIMAGELIST_H
#define WEEKIMAGELIST_H


#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "baseimagelist.h"
#include "dayofweek.h"


class WeekImageList : public BaseImageList {
private:
    QMap<DayOfWeek, int> images; // Використовуємо DayOfWeek як ключ
public:
    WeekImageList();
    WeekImageList(QString name, const QMap<DayOfWeek, int>& images);

    // Геттери та сеттери
    QMap<DayOfWeek, int> getImages() const;
    void setImages(const QMap<DayOfWeek, int>& newImages);
};

#endif // WEEKIMAGELIST_H
