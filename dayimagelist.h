#ifndef DAYIMAGELIST_H
#define DAYIMAGELIST_H

#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "baseimagelist.h"
struct TimeRangeImage {
    QString startTime;
    QString endTime;
    int imageId;
    int id;

    TimeRangeImage() : startTime(""), endTime(""), imageId(-1), id(-1) {}

    TimeRangeImage(const QString& start, const QString& end, int imageId, int id)
        : startTime(start), endTime(end), imageId(imageId), id(id) {}
};

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
