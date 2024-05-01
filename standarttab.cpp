#include "standarttab.h"
#include "ui_standarttab.h"
#include "style.h"
StandartTab::StandartTab(DBManager *dbManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StandartTab), dbManager(dbManager)
{
    ui->setupUi(this);
    imageManager = new ImageManager(dbManager);
    //images = dbManager->getAllImages();
    setStandartTabStyle();
}

StandartTab::~StandartTab()
{
    delete ui;
}

void StandartTab::showImage(int index)
{
    if (index >= 0 && index < imageManager->getsizeOfImages()) {
        QPixmap pixmap(imageManager->GetImageById(index).getUrl());
        ui->SliderImage->setPixmap(pixmap.scaled(ui->SliderImage->size(), Qt::KeepAspectRatio));
    }
}

void StandartTab::nextImage()
{
    currentIndex = (currentIndex + 1) % imageManager->getsizeOfImages();
    showImage(currentIndex);
}

void StandartTab::setStandartTabStyle()
{
    ui->StandartTabWidget->setStyleSheet(Style::getTabsStyle());
    ui->StandartTabButtonMenuWidget->setStyleSheet(Style::getStandartTabStyle());
    ui->StandartTabWlapperSliderWidget->setStyleSheet(Style::getStandartTabStyle());

    setSliderButtonIcon();
    showImage(currentIndex);
}

void StandartTab::setSliderButtonIcon()
{
    ui->SliderRightArrow->setIcon(QIcon(":/resource/SliderRightArrow.png"));
    ui->SliderRightArrow->setIconSize(QSize(65, 65));
    ui->SliderLeftArrow->setIcon(QIcon(":/resource/SliderLeftArrow.png"));
    ui->SliderLeftArrow->setIconSize(QSize(65, 65));
}

QImage StandartTab::loadImage(const QString &fileName)
{
    QImage image(fileName);
        if (image.isNull()) {
            qDebug() << "Failed to load image from file:" << fileName;
            QMessageBox::warning(nullptr, QObject::tr("Loading Error"), QObject::tr("Could not load the image from the file."));
        }
        return image;
}

std::unique_ptr<WlapperImage> StandartTab::createWlapperImage(const QString &fileName, const QImage &image)
{
    auto wlapperImage = std::make_unique<WlapperImage>();
       wlapperImage->setName(QFileInfo(fileName).fileName());
       wlapperImage->setUrl(fileName);
       wlapperImage->setHeight(image.height());
       wlapperImage->setWidth(image.width());
       return wlapperImage;
}

void StandartTab::displayImageInLabel(QLabel *label, const QString &filePath)
{
    QPixmap pixmap(filePath);
       if (!pixmap.isNull()) {
           label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
           label->setScaledContents(true);
           qDebug() << "Pixmap loaded successfully, Size:" << pixmap.size();
       } else {
           qDebug() << "Failed to load pixmap.";
       }
}

void StandartTab::previousImage()
{
    currentIndex = (currentIndex - 1 + imageManager->getsizeOfImages()) % imageManager->getsizeOfImages();
    showImage(currentIndex);
}
void StandartTab::on_StandartTabChooseButton_clicked(){
    dialogWindowListOfImage = new DialogWindowListOfImage(this->dbManager,this);
    dialogWindowListOfImage ->show();
    dialogWindowListOfImage->setStyleSheet(Style::getTabsStyle());

}
void StandartTab::on_StandartTabAddButton_clicked() {

   //MainWindow::addNewImage();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Wlapper"), "/wlapper", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));
    qDebug() << "File selected:" << fileName;

    if (!fileName.isEmpty()) {
        QImage image = loadImage(fileName);
        if (!image.isNull()) {
            auto wlapperImage = createWlapperImage(fileName, image);
            displayImageInLabel(ui->SliderImage, fileName);

            if (!dbManager->insertIntoImageTable(*wlapperImage)) {
                qDebug() << "Error inserting data into the database.";
            }
        }
    } else {
        qDebug() << "No file selected.";
    }
    imageManager->getImagesFromTable();
}


void StandartTab::on_SliderLeftArrow_clicked()
{
    previousImage();
}


void StandartTab::on_SliderRightArrow_clicked()
{
    nextImage();
}

bool StandartTab::setWallpaper(const QString &imagePath)
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

void StandartTab::on_StandartTabSetButton_clicked()
{
    setWallpaper(imageManager->GetImageById(currentIndex).getUrl());
}


void StandartTab::on_StandartTabDeleteButton_clicked()
{
imageManager->deleteImageById(currentIndex);

nextImage();
}

