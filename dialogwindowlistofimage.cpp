#include "dialogwindowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"
#include <QElapsedTimer>
#include <QDebug>
DialogWindowListOfImage::DialogWindowListOfImage(QWidget *parent, UIElementEventHandler *uiElementEventHandler) :
    QDialog(parent),
    ui(new Ui::DialogWindowListOfImage),uiElementEventHandler(uiElementEventHandler)
{

    ui->setupUi(this);
    //this->setAttribute(Qt::WA_DeleteOnClose);
    this->setStyleSheet(Style::getTabsStyle());
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
    imageList = SQLTableImageList::getInstance();
    scrollAreaConterinerWidget = new QWidget(this);
    scrollAreaManager = new ScrollAreaManager();
    interfaceAddition = new InterfaceAddition(this,uiElementEventHandler);
    imageLoader = new ImageLoader();
    scrollAreaManager->CreateScrollArea(this, scrollAreaConterinerWidget,WidgetGeometry(300,420,0,80));
    CreateListOfImageIntarface(); // Кінець заміру часу

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
                    throw WSExceptions("Image not found for ID: " + QString::number(imageId));
                }
            } else {
                throw WSExceptions("Failed to choose image.");
            }
        } else {
            throw WSExceptions("Image not loaded!");
        }
    } catch (const WSExceptions& ex) {
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

    delete imageLoader;
    delete interfaceAddition;
    delete scrollAreaManager;
    delete scrollAreaConterinerWidget;
    delete ui;




}
void DialogWindowListOfImage::closeEvent() {
    QDialog::hide();
}


