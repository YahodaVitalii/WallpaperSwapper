 #include "imageloader.h"

ImageLoader::ImageLoader(){
     dbImageTableManager = new ImageTableManager();
}

bool ImageLoader::ChooseImageFromFiles(QWidget* parent) {
    try {
        QString fileName = QFileDialog::getOpenFileName(parent, tr("Open Wlapper"), "/wlapper", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
        qDebug() << "File selected:" << fileName;

        if (fileName.isEmpty()) {
            throw WSException("No file selected.");
        }

        QImage image = loadImage(fileName);
        if (image.isNull()) {
            throw WSException("Failed to load image from file.");
        }

        auto wlapperImage = createWlapperImage(fileName, image);
        if (!dbImageTableManager->insertIntoTable(*wlapperImage)) {
            throw WSException("Error inserting data into the database.");
        }
        return true; // Return the ID of the last element
    } catch (const WSException& ex) {
        qDebug() << "Error:" << ex.getMessage();
    } catch (const QException& ex) {
        qDebug() << "Unexpected error:" << ex.what();
    }

    return false;
}
QImage ImageLoader::loadImage(const QString& fileName) {
    QImage image(fileName);
    if (image.isNull()) {
        qDebug() << "Failed to load image from file:" << fileName;
        QMessageBox::warning(nullptr, QObject::tr("Loading Error"), QObject::tr("Could not load the image from the file."));
    }
    return image;
}

std::unique_ptr<WallpaperImage> ImageLoader::createWlapperImage(const QString& fileName, const QImage& image) {
    auto wallpaperImage = std::make_unique<WallpaperImage>();
    wallpaperImage->setName(QFileInfo(fileName).fileName());
    wallpaperImage->setUrl(fileName);
    wallpaperImage->setHeight(image.height());
    wallpaperImage->setWidth(image.width());
    return wallpaperImage;
}
