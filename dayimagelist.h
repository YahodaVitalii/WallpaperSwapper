#ifndef DAYIMAGELIST_H
#define DAYIMAGELIST_H

#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
//#include "timerangeimage.h"
struct TimeRangeImage {
    QString startTime;
    QString endTime;
    int imageId;

    TimeRangeImage() : imageId(-1) {}
    TimeRangeImage(const QString& start, const QString& end, int id) : startTime(start), endTime(end), imageId(id) {}
};

class DayImageList {
private:
    int id;
    QString name;
    QVector<TimeRangeImage> images;

public:
    // Конструктори
    DayImageList();
    DayImageList(QString name, const QVector<TimeRangeImage>& images);

    QString getName() const;
    void setName(const QString& name);

    int getId() const;
    void setId(int newId);

    QVector<TimeRangeImage> getImages() const;
    void setImages(const QVector<TimeRangeImage>& newImages);

    // Методи серіалізації та десеріалізації у формат JSON
    QString toJsonString() const;
    void fromJsonString(const QString& jsonString);
};

#endif // DAYIMAGELIST_H
