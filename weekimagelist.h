#ifndef WEEKIMAGELIST_H
#define WEEKIMAGELIST_H


#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include "baseimagelist.h"


class WeekImageList : public BaseImageList {
private:
    QMap<QString, int> images;
public:
    WeekImageList();
    WeekImageList(QString name, const QMap<QString, int>& images);

    // Геттери та сеттери
    QMap<QString, int> getImages() const;
    void setImages(const QMap<QString, int>& newImages);
};

#endif // WEEKIMAGELIST_H
