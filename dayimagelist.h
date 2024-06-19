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
    int id; // Нове поле

    // Конструктор за замовчуванням, ініціалізація полів
    TimeRangeImage() : startTime(""), endTime(""), imageId(-1), id(-1) {}

    // Конструктор з параметрами, ініціалізація всіх полів
    TimeRangeImage(const QString& start, const QString& end, int imageId, int id)
        : startTime(start), endTime(end), imageId(imageId), id(id) {}
};

class DayImageList {
private:
    int id;
    QString name;


public:
     QVector<TimeRangeImage> images;
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
