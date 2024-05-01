#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include "sqlitedbmanager.h"
#include "wlapperimage.h"
class ImageManager
{
public:
    ImageManager(DBManager *dbManager);
   QVector<WlapperImage> getImages();
   void getImagesFromTable();
   WlapperImage GetImageById(int id);
   void deleteImageById(int id);
   int getsizeOfImages();

private:
    DBManager* dbManager;
     QVector<WlapperImage> images;
};

#endif // IMAGEMANAGER_H
