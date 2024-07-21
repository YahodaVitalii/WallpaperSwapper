#include "imageslist.h"

QVector<WlapperImage> ImagesList::images;

ImagesList::ImagesList(DBManager *dbManager):dbManager(dbManager)
{
   getImagesFromTable();
}

QVector<WlapperImage> ImagesList::getImages(){
return images;
}

void ImagesList::getImagesFromTable()
{
       images.clear(); // Очистка поточного списку перед оновленням
        images = dbManager->getAllImages();
        qDebug() << "Loaded images count: " << images.size();
}

WlapperImage ImagesList::GetImageByIndex(int index)
{
    return images[index];
}

void ImagesList::deleteImageByIndex(int index)
{
    dbManager->deleteImageById(images[index].getId());
    images.removeAt(index);
}

int ImagesList::getsizeOfImages()
{
    return images.size();
}

int ImagesList::findImageById(int imageId) {
    for (int i = 0; i < images.size(); ++i) {
        if (images[i].getId() == imageId) {
            return i;
        }
    }
    return -1;
}

void ImagesList::updateImageList()
{
   getImagesFromTable();
}
