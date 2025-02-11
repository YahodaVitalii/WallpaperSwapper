#include "windowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"
#include <QElapsedTimer>
#include <QDebug>
DialogWindowListOfImage::DialogWindowListOfImage(QWidget *parent, UIElementEventHandler *uiElementEventHandler) :
    BaseDialogWindow(parent, uiElementEventHandler), ui(new Ui::DialogWindowListOfImage)
{
    ui->setupUi(this);
    imageList = SQLTableImageList::getInstance();
    imageLoader = new ImageLoader();
    initializeInterface();
}

void DialogWindowListOfImage::CreateListOfImageIntarface()
{
    for(int i = 0; i<imageList->getsizeOfImages();i++){
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->BuildListOfImageItem(i));
    }
}

void DialogWindowListOfImage::on_ListOfImageMenuBarPlusButton_clicked()
{
    try {
        if (imageLoader->ChooseImageFromFiles()) {
            imageList->getImagesFromTable();

            int imageId = imageList->getImages().last().getId();
            if (imageId != -1) {
                int imageIndex = imageList->findImageById(imageId);
                if (imageIndex != -1) {
                    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->BuildListOfImageItem(imageIndex));
                } else {
                    throw WSException("Image not found for ID: " + QString::number(imageId));
                }
            } else {
                throw WSException("Failed to choose image.");
            }
        } else {
            throw WSException("Image not loaded!");
        }
    } catch (const WSException& ex) {
        qDebug() << "Error:" << ex.getMessage();
    } catch (const QException& ex) {
        qDebug() << "Unexpected error:" << ex.what();
    }
}
//void DialogWindowListOfImage::on_buttonDelete_clicked() {
//    int index = sender()->property("imageIndex").toInt();
//    imageManager->deleteImageByIndex(index);
//    qDebug() <<index;
//    //QLayoutItem *child;
////    while ((child = containerWidget->layout()->takeAt(0)) != nullptr) {
////        delete child->widget();
////        delete child;
////    }
//    CreateListOfImageIntarface();
//}

DialogWindowListOfImage::~DialogWindowListOfImage()
{
    delete scrollAreaManager;
    delete scrollAreaConterinerWidget;
    delete ui;
}

void DialogWindowListOfImage::initializeInterface()
{
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
    scrollAreaConterinerWidget = new QWidget(this);
    scrollAreaManager->CreateScrollArea(this, scrollAreaConterinerWidget,WidgetGeometry(300,420,0,80));
    CreateListOfImageIntarface();
}


