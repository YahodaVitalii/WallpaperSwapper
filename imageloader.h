#ifndef IMAGELOADER_H
#define IMAGELOADER_H



#include <QImage>
#include <QString>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <Windows.h>
#include "wallpaperimage.h"
#include "wsexception.h"
#include "sqlitedbmanager.h"
#include "imagetablemanager.h"

class ImageLoader : public QObject
{
    Q_OBJECT
private:

    DBManager* dbManager;
    ImageTableManager* dbImageTableManager;

    QImage loadImage(const QString& fileName);
    std::unique_ptr<WallpaperImage> createWlapperImage(const QString& fileName, const QImage& image);
public:
    ImageLoader();
    bool ChooseImageFromFiles(QWidget* parent = nullptr);

};

#endif // IMAGELOADER_H
