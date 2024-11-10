#ifndef RANDOMIMAGELIST_H
#define RANDOMIMAGELIST_H

#include <QVector>
#include <QDateTime>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "baseimagelist.h"

class RandomImageList : public BaseImageList {
private:
    QDateTime timeInterval;
    QVector<int> imageIds;

public:
    RandomImageList();
    RandomImageList(QString name, const QDateTime& interval, const QVector<int>& ids);
    QDateTime getTimeInterval() const;
    void setTimeInterval(const QDateTime& newTimeInterval);

    QVector<int> getImageIds() const;
    void setImageIds(const QVector<int>& newImageIds);
};


#endif // RANDOMIMAGELIST_H
