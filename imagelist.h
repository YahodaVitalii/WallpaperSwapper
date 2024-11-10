#ifndef ImageList_H
#define ImageList_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include <Windows.h>
#include <QMessageBox>
#include "sqlitedbmanager.h"
#include "wallpaperimage.h"
#include "scrollareamanager.h"
#include "imageloader.h"
#include "imagetablemanager.h"


class ImageList : public QObject
{
    Q_OBJECT
public:
    explicit ImageList(QObject* parent = nullptr) : QObject(parent) {}

    // Віртуальні методи, які повинні бути реалізовані в похідних класах
    virtual void getImagesFromTable() = 0;
    virtual QVector<WallpaperImage> getImages()  = 0;
    virtual WallpaperImage GetImageByIndex(int index)  = 0;
    virtual int findImageById(int imageId)  = 0;
    //virtual void deleteImageByIndex(int index) = 0;
    virtual int getsizeOfImages()  = 0;

signals:
    void imagesUpdated();

public slots:
    virtual void updateImageList() = 0;
};

#endif // ImageList_H
