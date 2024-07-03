#include "dialogwindowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"
DialogWindowListOfImage::DialogWindowListOfImage(DBManager* dbManager, ImageManager *imageManager, InterfaceAddition *interfaceAddition, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindowListOfImage),
    dbManager(dbManager),interfaceAddition(interfaceAddition),imageManager(imageManager)
    //scrollArea(new QScrollArea(this))
{
    ui->setupUi(this);
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
    scrollAreaConterinerWidget = new QWidget(this);
    interfaceAddition->CreateScrollArea(this, scrollAreaConterinerWidget,300,420,0,80);
    CreateListOfImageIntarface();
}

void DialogWindowListOfImage::CreateListOfImageIntarface()
{
    for(int i = 0; i<imageManager->getsizeOfImages();i++){
       interfaceAddition->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->CreateListOfImageItem(i));
    }
}
void DialogWindowListOfImage::on_ListOfImageMenuBarPlusButton_clicked() {
    int imageId = imageManager->ChooseImageFromFiles();
    if (imageId != -1) {  // Перевірте, що ID є дійсним
        int imageIndex = imageManager->findImageById(imageId);
        if (imageIndex != -1) { // Перевірте, чи знайдено зображення з таким індексом
           interfaceAddition->setWidgetIntoScrollArea(scrollAreaConterinerWidget, interfaceAddition->CreateListOfImageItem(imageIndex));
        } else {
            qDebug() << "Image not found for ID:" << imageId;
            // Обробити помилку, якщо зображення не знайдено
        }
    } else {
        qDebug() << "Failed to choose image.";
        // Обробити помилку, якщо не вдалося вибрати зображення
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
