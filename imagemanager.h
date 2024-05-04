#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include <Windows.h>
#include <QMessageBox>
#include "sqlitedbmanager.h"
#include "wlapperimage.h"

class ImageManager : public QObject
{
    Q_OBJECT

public:
    explicit ImageManager(DBManager *dbManager);
    int ChooseImageFromFiles(QWidget* parent = nullptr);  // Only one declaration needed
    QVector<WlapperImage> getImages();
    void getImagesFromTable();
    WlapperImage GetImageByIndex(int index);
    void deleteImageByIndex(int index);
    int getsizeOfImages();
    QImage loadImage(const QString& fileName);
    std::unique_ptr<WlapperImage> createWlapperImage(const QString& fileName, const QImage& image);
    bool setWallpaper(const QString &imagePath);
    int findImageById(int imageId);

private:
    DBManager* dbManager;
    QVector<WlapperImage> images;
};
#endif // IMAGEMANAGER_H
