#include "imagemanager.h"

ImageManager::ImageManager(DBManager *dbManager):dbManager(dbManager)
{
   getImagesFromTable();
}

QVector<WlapperImage> ImageManager::getImages(){
return images;
}

void ImageManager::getImagesFromTable()
{
    images = dbManager->getAllImages();
}

WlapperImage ImageManager::GetImageById(int id)
{
    return images[id];
}

void ImageManager::deleteImageById(int id)
{
    dbManager->deleteImageById(images[id].getId());
    images.removeAt(id);
}

int ImageManager::getsizeOfImages()
{
   return images.size();
}
