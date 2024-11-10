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
    imageSlider = new StandartTabImageSlider(WidgetGeometry(540,300,50,20),this);

    connect(uiElementEventHandler, &UIElementEventHandler::imageSelected, this, &StandartTab::updateImage);

}

StandartTab::~StandartTab()
{
    delete ui;
}

void StandartTab::setStandartTabStyle()
{
    ui->StandartTabWidget->setStyleSheet(Style::getTabsStyle());
    ui->StandartTabButtonMenuWidget->setStyleSheet(Style::getStandartTabStyle());
}

void StandartTab::updateImage(int index)
{
    currentIndex = index;
    imageSlider->ChangeCurrentImage(currentIndex);
    dialogWindowController ->Close();
}

void StandartTab::on_StandartTabChooseButton_clicked()
{
    dialogWindowController ->Open(this);
}

void StandartTab::on_StandartTabAddButton_clicked()
{
    if(imageLoader->ChooseImageFromFiles()){
        imageList ->getImagesFromTable();

        int imageId = imageList->getImages().last().getId();
        if (imageId != -1) {
            currentIndex = imageList->findImageById(imageId);
            if (currentIndex != -1) {
                imageSlider->ChangeCurrentImage(currentIndex);
            }
        }
    }else{
        qDebug() << "Image not loadet!";
    }
}

void StandartTab::on_StandartTabSetButton_clicked()
{
    currentIndex = imageSlider->GetCurrentIndex();
    wallpaperSetter-> setWallpaper(imageList->GetImageByIndex(currentIndex).getUrl());
}

void StandartTab::on_StandartTabDeleteButton_clicked()
{

}



