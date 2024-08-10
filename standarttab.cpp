#include "standarttab.h"
#include "ui_standarttab.h"
#include "style.h"
StandartTab::StandartTab(DBManager *dbManager, ImageList *imageList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StandartTab), dbManager(dbManager),imageList(imageList)
{
    ui->setupUi(this);
    setStandartTabStyle();
   uiElementEventHandler = new UIElementEventHandler();
    interfaceAddition = new InterfaceAddition(parent,uiElementEventHandler);
    imageLoader = new ImageLoader();
    wallpaperSetter = new WallpaperSetter();
    dialogWindowController = new DialogWindowController(uiElementEventHandler);

    connect(uiElementEventHandler, &UIElementEventHandler::imageSelected, this, &StandartTab::updateImage);

}

StandartTab::~StandartTab()
{
    delete ui;
}

void StandartTab::showImage(int index)
{
    if (index >= 0 && index < imageList->getsizeOfImages()) {
        QPixmap pixmap(imageList->GetImageByIndex(index).getUrl());
        ui->SliderImage->setPixmap(pixmap.scaled(ui->SliderImage->size(), Qt::KeepAspectRatio));
    }
}

void StandartTab::nextImage()
{
    currentIndex = (currentIndex + 1) % imageList->getsizeOfImages();
    showImage(currentIndex);
}
void StandartTab::previousImage()
{
    currentIndex = (currentIndex - 1 + imageList->getsizeOfImages()) % imageList->getsizeOfImages();
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


void StandartTab::on_StandartTabChooseButton_clicked(){
    dialogWindowController ->Open(this);
}
void StandartTab::on_StandartTabAddButton_clicked() {
    if(imageLoader->ChooseImageFromFiles()){
        imageList ->getImagesFromTable();

        int imageId = imageList->getImages().last().getId();
        if (imageId != -1) {  // Перевірте, що ID є дійсним
            currentIndex = imageList->findImageById(imageId); // Вам потрібно написати цю функцію
            if (currentIndex != -1) { // Переконайтеся, що індекс існує
                displayImageInLabel(ui->SliderImage, imageList->GetImageByIndex(currentIndex).getUrl());
                showImage(currentIndex);
            }
        }
    }else{
        qDebug() << "Image not loadet!";
    }
}
void StandartTab::on_SliderLeftArrow_clicked()
{
    previousImage();
}

void StandartTab::on_SliderRightArrow_clicked()
{
    nextImage();
}


void StandartTab::on_StandartTabSetButton_clicked()
{
    wallpaperSetter-> setWallpaper(imageList->GetImageByIndex(currentIndex).getUrl());
}

void StandartTab::on_StandartTabDeleteButton_clicked()
{
    imageList->deleteImageByIndex(currentIndex);

    nextImage();
}

void StandartTab::updateImage(int index)
{
    currentIndex = index;
    showImage(currentIndex);
    dialogWindowController ->Close();
}

