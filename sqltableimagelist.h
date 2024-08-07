#ifndef SQLTABLEIMAGELIST_H
#define SQLTABLEIMAGELIST_H
#include "imageslist.h"

class SQLTableImageList : public ImageList
{
    Q_OBJECT
private:
    DBManager* dbManager;
    ImageLoader* imageLoader;
    DBImageTableManager* dbImageTableManager;
    QVector<WlapperImage> images;

    explicit SQLTableImageList(QObject* parent = nullptr); // Приватний конструктор для Singleton

    static SQLTableImageList* instance; // Статичний вказівник на екземпляр

public:
    static SQLTableImageList* getInstance(); // Метод для доступу до єдиного екземпляра

    // Заборонити копіювання та присвоєння
    SQLTableImageList(const SQLTableImageList&) = delete;
    SQLTableImageList& operator=(const SQLTableImageList&) = delete;

    // Реалізація абстрактних методів
    void getImagesFromTable() override;
    QVector<WlapperImage> getImages() override;
    WlapperImage GetImageByIndex(int index) override;
    int findImageById(int imageId) override;
    void deleteImageByIndex(int index) override;
    int getsizeOfImages() override;

public slots:
    void updateImageList() override;
};

#endif // SQLTABLEIMAGELIST_H
