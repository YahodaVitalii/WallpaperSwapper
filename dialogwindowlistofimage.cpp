#include "dialogwindowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"
DialogWindowListOfImage::DialogWindowListOfImage(DBManager* dbManager, ImagesList *imageManager, InterfaceAddition *interfaceAddition, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindowListOfImage),
    dbManager(dbManager),interfaceAddition(interfaceAddition),imageManager(imageManager)
    //scrollArea(new QScrollArea(this))
{
    ui->setupUi(this);
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
    scrollAreaConterinerWidget = new QWidget(this);
    scrollAreaManager = new ScrollAreaManager();
    imageLoader = new ImageLoader(dbManager);
    scrollAreaManager->CreateScrollArea(this, scrollAreaConterinerWidget,300,420,0,80);
    CreateListOfImageIntarface();

}

void DialogWindowListOfImage::CreateListOfImageIntarface()
{
    for(int i = 0; i<imageManager->getsizeOfImages();i++){
       scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->CreateListOfImageItem(i));
    }
}
void DialogWindowListOfImage::on_ListOfImageMenuBarPlusButton_clicked() {
    try {
        if (imageLoader->ChooseImageFromFiles()) {
            imageManager->getImagesFromTable();

            int imageId = imageManager->getImages().last().getId();
            if (imageId != -1) {
                int imageIndex = imageManager->findImageById(imageId);
                if (imageIndex != -1) {
                    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->CreateListOfImageItem(imageIndex));
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


//void DialogWindowListOfImage::on_buttonInfo_clicked() {
//    qDebug() << "Info button clicked";
//}

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

void DialogWindowListOfImage::showDialogWindow()
{
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerWidget);
    CreateListOfImageIntarface();
    this->show();
}
