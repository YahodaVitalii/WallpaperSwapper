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
    QString name;
    QDateTime timeInterval;


public:
    QVector<int> imageIds;
    // Конструктори
    RandomImageList();
    RandomImageList(QString name, const QDateTime& interval, const QVector<int>& ids);

    QString getName() const;
    void setName(QString name);

    // Геттери та сеттери
    int getId() const;
    void setId(int newId);

    QDateTime getTimeInterval() const;
    void setTimeInterval(const QDateTime& newTimeInterval);

    QVector<int> getImageIds() const;
    void setImageIds(const QVector<int>& newImageIds);

    // Методи серіалізації та десеріалізації у формат JSON
    QString toJsonString() const;
    void fromJsonString(const QString& jsonString);
};

#endif // RANDOMIMAGELIST_H
