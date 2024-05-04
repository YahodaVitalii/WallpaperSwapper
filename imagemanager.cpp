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
    images.clear(); // Очистка поточного списку перед оновленням
        images = dbManager->getAllImages();
        qDebug() << "Loaded images count: " << images.size();
}

WlapperImage ImageManager::GetImageByIndex(int index)
{
    return images[index];
}

void ImageManager::deleteImageByIndex(int index)
{
    dbManager->deleteImageById(images[index].getId());
    images.removeAt(index);
}

int ImageManager::getsizeOfImages()
{
    return images.size();
}

QImage ImageManager::loadImage(const QString &fileName)
{
    QImage image(fileName);
        if (image.isNull()) {
            qDebug() << "Failed to load image from file:" << fileName;
            QMessageBox::warning(nullptr, QObject::tr("Loading Error"), QObject::tr("Could not load the image from the file."));
        }
        return image;
}

std::unique_ptr<WlapperImage> ImageManager::createWlapperImage(const QString &fileName, const QImage &image)
{
    auto wlapperImage = std::make_unique<WlapperImage>();
       wlapperImage->setName(QFileInfo(fileName).fileName());
       wlapperImage->setUrl(fileName);
       wlapperImage->setHeight(image.height());
       wlapperImage->setWidth(image.width());
       return wlapperImage;
}



bool ImageManager::setWallpaper(const QString &imagePath)
{
    std::wstring path = imagePath.toStdWString();

    BOOL result = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, static_cast<void*>(const_cast<wchar_t*>(path.c_str())),
                                        SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
    if (result) {
        return true;
    } else {
        qDebug() << "Failed to set wallpaper. Error:" << GetLastError();
        return false;
    }
}

int ImageManager::ChooseImageFromFiles(QWidget* parent) {
    QString fileName = QFileDialog::getOpenFileName(parent, tr("Open Wlapper"), "/wlapper", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
    qDebug() << "File selected:" << fileName;

    if (!fileName.isEmpty()) {
        QImage image = loadImage(fileName);
        if (!image.isNull()) {
            auto wlapperImage = createWlapperImage(fileName, image);
            if (dbManager->insertIntoImageTable(*wlapperImage)) {
                getImagesFromTable(); // Оновлення списку після додавання нового зображення
                if (!images.isEmpty()) {
                    return images.last().getId(); // Повернення ID останнього елемента
                }
            } else {
                qDebug() << "Error inserting data into the database.";
            }
        }
    } else {
        qDebug() << "No file selected.";
    }
    return -1; // Повернення -1, якщо файл не був обраний або сталася помилка
}
int ImageManager::findImageById(int imageId) {
    for (int i = 0; i < images.size(); ++i) {
        if (images[i].getId() == imageId) {
            return i;
        }
    }
    return -1;  // Повернути -1, якщо зображення з таким ID не знайдено
}
