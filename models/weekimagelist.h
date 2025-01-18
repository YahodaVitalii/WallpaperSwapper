#ifndef WEEKIMAGELIST_H
#define WEEKIMAGELIST_H


#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "baseimagelist.h"
#include "enums/dayofweek.h"


class WeekImageList : public BaseImageList {
private:
    QMap<DayOfWeek, int> images;
public:
    WeekImageList();
    WeekImageList(QString name, const QMap<DayOfWeek, int>& images);

    QMap<DayOfWeek, int> getImages() const;
    void setImages(const QMap<DayOfWeek, int>& newImages);
};

#endif // WEEKIMAGELIST_H
