#ifndef IMAGELOADER_H
#define IMAGELOADER_H



#include <QImage>
#include <QString>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <Windows.h>
#include "wlapperimage.h"
#include "wsexeptions.h"
#include "sqlitedbmanager.h"
#include "dbimagetablemanager.h"

class ImageLoader : public QObject
{
    Q_OBJECT
private:

    DBManager* dbManager;
    DBImageTableManager* dbImageTableManager;

    QImage loadImage(const QString& fileName);
    std::unique_ptr<WlapperImage> createWlapperImage(const QString& fileName, const QImage& image);
public:
    ImageLoader();
    bool ChooseImageFromFiles(QWidget* parent = nullptr);

};

#endif // IMAGELOADER_H
