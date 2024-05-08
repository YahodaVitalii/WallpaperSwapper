#include "dialogwindowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"
DialogWindowListOfImage::DialogWindowListOfImage(DBManager* dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindowListOfImage),
    dbManager(dbManager),
    scrollArea(new QScrollArea(this))
    //containerWidget(new QWidget())
{
    ui->setupUi(this);
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
    imageManager = new ImageManager(dbManager);
    interfaceAddition = new InterfaceAddition(parent,dbManager,imageManager);

    scrollArea->setFixedSize(300, 420);
    scrollArea->move(0, 80);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(interfaceAddition->containerWidget);

    CreateListOfImageIntarface();
}

void DialogWindowListOfImage::CreateListOfImageIntarface()
{
    for(int i = 0; i<imageManager->getsizeOfImages();i++){
        interfaceAddition->CreateListOfImageItem(i);
    }
}


void DialogWindowListOfImage::on_ListOfImageMenuBarPlusButton_clicked(){
    int imageId = imageManager->ChooseImageFromFiles();
    if (imageId != -1) {  // Перевірте, що ID є дійсним
     interfaceAddition->CreateListOfImageItem(imageManager->findImageById(imageId));
    }
}
//void DialogWindowListOfImage::on_buttonFullSize_clicked() {
//    QString imageUrl = imageManager->GetImageByIndex(sender()->property("imageIndex").toInt()).getUrl();
//    QDesktopServices::openUrl(QUrl("file:///" + imageUrl));
//}

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

//void DialogWindowListOfImage::on_buttonImage_clicked()
//{
//    int index = sender()->property("imageIndex").toInt();
//    emit imageSelected(index);
//}
DialogWindowListOfImage::~DialogWindowListOfImage()
{
    delete ui;
}
