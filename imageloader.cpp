#include "imageloader.h"

ImageLoader::ImageLoader(DBManager *dbManager):dbManager(dbManager){
}

bool ImageLoader::ChooseImageFromFiles(QWidget* parent) {
    try {
        QString fileName = QFileDialog::getOpenFileName(parent, tr("Open Wlapper"), "/wlapper", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
        qDebug() << "File selected:" << fileName;

        if (fileName.isEmpty()) {
            throw WSExeptions("No file selected.");
        }

        QImage image = loadImage(fileName);
        if (image.isNull()) {
            throw WSExeptions("Failed to load image from file.");
        }

        auto wlapperImage = createWlapperImage(fileName, image);
        if (!dbManager->insertIntoImageTable(*wlapperImage)) {
            throw WSExeptions("Error inserting data into the database.");
        }

//        getImagesFromTable();
//        if (images.isEmpty()) {
//            throw WSExeptions("No images found in the table after insertion.");
//        }

        return true; // Return the ID of the last element
    } catch (const WSExeptions& ex) {
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

std::unique_ptr<WlapperImage> ImageLoader::createWlapperImage(const QString& fileName, const QImage& image) {
    auto wlapperImage = std::make_unique<WlapperImage>();
    wlapperImage->setName(QFileInfo(fileName).fileName());
    wlapperImage->setUrl(fileName);
    wlapperImage->setHeight(image.height());
    wlapperImage->setWidth(image.width());
    return wlapperImage;
}
