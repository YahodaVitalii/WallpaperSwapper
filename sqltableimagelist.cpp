#include "sqltableimagelist.h"

SQLTableImageList* SQLTableImageList::instance = nullptr;

SQLTableImageList::SQLTableImageList(QObject* parent)
    : ImageList(parent), dbImageTableManager(new DBImageTableManager())
{
    getImagesFromTable();
}

// Статичний метод для доступу до єдиного екземпляра
SQLTableImageList* SQLTableImageList::getInstance()
{
    if (instance == nullptr) {
        instance = new SQLTableImageList();
    }
    return instance;
}

QVector<WlapperImage> SQLTableImageList::getImages() {
    return images;
}

void SQLTableImageList::getImagesFromTable()
{
    images.clear(); // Очистка поточного списку перед оновленням
    images = dbImageTableManager->getAllImages();
    qDebug() << "Loaded images count: " << images.size();
    emit imagesUpdated(); // Відправлення сигналу про оновлення зображень
}

WlapperImage SQLTableImageList::GetImageByIndex(int index)
{
    return images.at(index);
}

void SQLTableImageList::deleteImageByIndex(int index)
{
    dbManager->deleteImageById(images[index].getId());
    images.removeAt(index);
    emit imagesUpdated(); // Відправлення сигналу про оновлення зображень
}

int SQLTableImageList::getsizeOfImages()
{
    return images.size();
}

int SQLTableImageList::findImageById(int imageId) {
    for (int i = 0; i < images.size(); ++i) {
        if (images[i].getId() == imageId) {
            return i;
        }
    }
    return -1;
}

void SQLTableImageList::updateImageList()
{
    getImagesFromTable();
}
