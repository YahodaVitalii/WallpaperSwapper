#include "weekimagelist.h"

WeekImageList::WeekImageList() : BaseImageList() {}

WeekImageList::WeekImageList(QString name, const QMap<DayOfWeek, int>& images)
    : BaseImageList(name), images(images) {}

QMap<DayOfWeek, int> WeekImageList::getImages() const {
    return images;
}

void WeekImageList::setImages(const QMap<DayOfWeek, int>& newImages) {
    images = newImages;
}
