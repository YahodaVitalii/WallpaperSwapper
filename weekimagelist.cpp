#include "weekimagelist.h"

WeekImageList::WeekImageList() : BaseImageList() {}

WeekImageList::WeekImageList(QString name, const QMap<QString, int>& images)
    : BaseImageList(name), images(images) {}

QMap<QString, int> WeekImageList::getImages() const {
    return images;
}

void WeekImageList::setImages(const QMap<QString, int>& newImages) {
    images = newImages;
}
