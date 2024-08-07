#include "dialogwindowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"
DialogWindowListOfImage::DialogWindowListOfImage(DBManager* dbManager, ImageList *imageList, InterfaceAddition *interfaceAddition, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindowListOfImage),
    dbManager(dbManager),interfaceAddition(interfaceAddition),imageList(imageList)
    //scrollArea(new QScrollArea(this))
{
    ui->setupUi(this);
    this->setStyleSheet(Style::getTabsStyle());
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
    scrollAreaConterinerWidget = new QWidget(this);
    scrollAreaManager = new ScrollAreaManager();
    imageLoader = new ImageLoader();
    scrollAreaManager->CreateScrollArea(this, scrollAreaConterinerWidget,300,420,0,80);
    CreateListOfImageIntarface();


}

void DialogWindowListOfImage::CreateListOfImageIntarface()
{
    for(int i = 0; i<imageList->getsizeOfImages();i++){
       scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->BuildListOfImageItem(i));
    }
}
void DialogWindowListOfImage::on_ListOfImageMenuBarPlusButton_clicked() {
    try {
        if (imageLoader->ChooseImageFromFiles()) {
            imageList->getImagesFromTable();

            int imageId = imageList->getImages().last().getId();
            if (imageId != -1) {
                int imageIndex = imageList->findImageById(imageId);
                if (imageIndex != -1) {
                    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->BuildListOfImageItem(imageIndex));
                } else {
                    throw WSExeptions("Image not found for ID: " + QString::number(imageId));
                }
            } else {
                throw WSExeptions("Failed to choose image.");
            }
        } else {
            throw WSExeptions("Image not loaded!");
        }
    } catch (const WSExeptions& ex) {
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
 delete ui;
}
void DialogWindowListOfImage::closeEvent() {
    QDialog::hide();
}


