#include "dayimagelist.h"

DayImageList::DayImageList() : BaseImageList() {}

DayImageList::DayImageList(QString name, const QVector<TimeRangeImage>& images)
    : BaseImageList(name), images(images) {}

QVector<TimeRangeImage> DayImageList::getImages() const {
    return images;
}

void DayImageList::setImages(const QVector<TimeRangeImage>& newImages) {
    images = newImages;
}

