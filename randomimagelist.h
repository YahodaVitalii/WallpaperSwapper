#ifndef RANDOMIMAGELIST_H
#define RANDOMIMAGELIST_H

#include <QVector>
#include <QDateTime>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class RandomImageList {
private:
    int id;
    QDateTime timeInterval;
    QVector<int> imageIds;

public:
    // Конструктори
    RandomImageList();
    RandomImageList(const QDateTime& interval, const QVector<int>& ids);

    // Геттери та сеттери
    int getId() const;
    void setId(int newId);

    QDateTime getTimeInterval() const;
    void setTimeInterval(const QDateTime& newTimeInterval);

    QVector<int> getImageIds() const;
    void setImageIds(const QVector<int>& newImageIds);

    // Методи серіалізації та десеріалізації у формат JSON
    QString toJsonString() const;
    static RandomImageList fromJsonString(const QString& jsonString);
};

#endif // RANDOMIMAGELIST_H
