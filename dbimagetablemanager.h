#ifndef DBIMAGETABLEMANAGER_H
#define DBIMAGETABLEMANAGER_H
#include<QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include"randomimagelist.h"
#include "wsexeptions.h"
#include "wallpaperimage.h"
#include "sqlitedbmanager.h"

class DBImageTableManager
{
public:
    DBImageTableManager();
    bool checkDatabaseConnection();
    bool insertIntoImageTable(const WallpaperImage& wallpaperImage);
    QVector<WallpaperImage> getAllImages();
    bool deleteImageById(int imageId);
};

#endif // DBIMAGETABLEMANAGER_H
