#ifndef IMAGETABLEMANAGER_H
#define IMAGETABLEMANAGER_H
#include "dbtablemanager.h"
#include "wallpaperimage.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

class ImageTableManager : public DBTableManager<WallpaperImage, QVector<WallpaperImage>>
{
public:
    bool insertIntoTable(const WallpaperImage& wallpaperImage) override;
    QVector<WallpaperImage> getAllRecords() override;
    bool deleteImageById(int imageId);

};

#endif // IMAGETABLEMANAGER_H
