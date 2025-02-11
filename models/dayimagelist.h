#ifndef DAYIMAGELIST_H
#define DAYIMAGELIST_H

#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "baseimagelist.h"
#include "struct/timerangeimage.h"

class DayImageList : public BaseImageList {
private:
    QVector<TimeRangeImage> images;
public:
    DayImageList();
    DayImageList(QString name, const QVector<TimeRangeImage>& images);

    QVector<TimeRangeImage> getImages() const;
    void setImages(const QVector<TimeRangeImage>& newImages);
};

#endif // DAYIMAGELIST_H
