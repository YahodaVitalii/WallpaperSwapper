#ifndef DBIMAGETABLEMANAGER_H
#define DBIMAGETABLEMANAGER_H
#include<QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include"randomimagelist.h"
#include "wsexeptions.h"
#include "wlapperimage.h"
#include "sqlitedbmanager.h"

class DBImageTableManager
{
public:
    DBImageTableManager();
    bool checkDatabaseConnection();
    bool insertIntoImageTable(const WlapperImage& wlapperImage);
    QVector<WlapperImage> getAllImages();
    bool deleteImageById(int imageId);
};

#endif // DBIMAGETABLEMANAGER_H
