#ifndef IMAGESLIST_H
#define IMAGESLIST_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include <Windows.h>
#include <QMessageBox>
#include "sqlitedbmanager.h"
#include "wlapperimage.h"
#include "scrollareamanager.h"
#include "imageloader.h"
#include "dbimagetablemanager.h"

class ImagesList : public QObject
{
    Q_OBJECT
private:
    DBManager* dbManager;
    static  QVector<WlapperImage> images;
    ImageLoader* imageLoader;
    DBImageTableManager* dbImageTableManager;

public:
    explicit ImagesList();
    void getImagesFromTable();
    QVector<WlapperImage> getImages();
    WlapperImage GetImageByIndex(int index);
    int findImageById(int imageId);
    void deleteImageByIndex(int index);
    int getsizeOfImages();

signals:
    void imagesUpdated();
private slots:
    void updateImageList();
};
#endif // IMAGESLIST_H
