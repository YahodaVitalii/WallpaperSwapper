#ifndef SQLTABLEIMAGELIST_H
#define SQLTABLEIMAGELIST_H
#include "imagelist.h"

class SQLTableImageList : public ImageList
{
    Q_OBJECT
private:
    DBManager* dbManager;
    ImageLoader* imageLoader;
    ImageTableManager* dbImageTableManager;
    QVector<WallpaperImage> images;

    explicit SQLTableImageList(QObject* parent = nullptr); // Приватний конструктор для Singleton

    static SQLTableImageList* instance; // Статичний вказівник на екземпляр

public:
    static SQLTableImageList* getInstance(); // Метод для доступу до єдиного екземпляра

    SQLTableImageList(const SQLTableImageList&) = delete;
    SQLTableImageList& operator=(const SQLTableImageList&) = delete;

    void getImagesFromTable() override;
    QVector<WallpaperImage> getImages() override;
    WallpaperImage GetImageByIndex(int index) override;
    int findImageById(int imageId) override;
    //void deleteImageByIndex(int index) override;
    int getsizeOfImages() override;

public slots:
    void updateImageList() override;
};

#endif // SQLTABLEIMAGELIST_H
