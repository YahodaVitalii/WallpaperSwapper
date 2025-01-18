#include "randomimagelist.h"
RandomImageList::RandomImageList() : BaseImageList() {}

RandomImageList::RandomImageList(QString name, const QDateTime& interval, const QVector<int>& ids)
    : BaseImageList(name), timeInterval(interval), imageIds(ids) {}

QDateTime RandomImageList::getTimeInterval() const {
    return timeInterval;
}

void RandomImageList::setTimeInterval(const QDateTime& newTimeInterval) {
    timeInterval = newTimeInterval;
}

QVector<int> RandomImageList::getImageIds() const {
    return imageIds;
}

void RandomImageList::setImageIds(const QVector<int>& newImageIds) {
    imageIds = newImageIds;
}
