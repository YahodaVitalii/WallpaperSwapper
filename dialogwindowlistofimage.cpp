#include "dialogwindowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"
DialogWindowListOfImage::DialogWindowListOfImage(DBManager* dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindowListOfImage),
    dbManager(dbManager),
    scrollArea(new QScrollArea(this)),
    containerWidget(new QWidget())
{
    ui->setupUi(this);
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
    imageManager = new ImageManager(dbManager);

    scrollArea->setFixedSize(300, 420);
    scrollArea->move(0, 80);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(containerWidget);

    QVBoxLayout *layout = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(layout);

    listItemCordinate_y = 0;
    CreateListOfImageIntarface();
}

void DialogWindowListOfImage::CreateListOfImageIntarface()
{
    listItemCordinate_y= 80;
    for(int i = 0; i<imageManager->getsizeOfImages();i++){
        CreateListOfImageItem(listItemCordinate_y,i);
        qDebug()<<listItemCordinate_y;
        listItemCordinate_y+=140;

    }
}

void DialogWindowListOfImage::CreateListOfImageItem(int listItemCordinate_y, int index)
{

    QWidget* listItemMeinWidget = new QWidget();
    listItemMeinWidget->setStyleSheet(Style::getImageListStyle());
    listItemMeinWidget->setFixedSize(260, 120);
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(containerWidget->layout());
    layout->addWidget(listItemMeinWidget);
    // Position at top-left corner of the dialog initially
    listItemMeinWidget->move(20, listItemCordinate_y);
    // listItemMeinWidget->setProperty("imageIndex", index);

    listItemMeinWidget->show();

    QLabel* label = new QLabel(listItemMeinWidget);
    //label->setStyleSheet("background-color: rgb(0, 225, 0);");
    label->setFixedSize(220, 110);
    label->move(5, 5);

    QPixmap pixmap(imageManager->GetImageByIndex(index).getUrl());
    label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
    label->setScaledContents(true);
    label->show();

    QPushButton* buttonImage = new QPushButton(listItemMeinWidget);
    buttonImage->setObjectName("buttonImage");  // Встановлення об'єктного імені
    buttonImage->setFixedSize(220, 110);
    buttonImage->move(5, 5);
    buttonImage->show();
    buttonImage->setProperty("imageIndex", index);
    connect(buttonImage, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonImage_clicked);

    QPushButton* buttonFullSize = new QPushButton(listItemMeinWidget);
    buttonFullSize->setFixedSize(25, 25);
    buttonFullSize->move(230, 20);
    buttonFullSize-> setIcon(QIcon(":/resource/Full@3x.png"));
    buttonFullSize->setIconSize(QSize(25, 25));
    buttonFullSize->show();
    buttonFullSize->setProperty("imageIndex", index);
    connect(buttonFullSize, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonFullSize_clicked);

    QPushButton* buttonInfo = new QPushButton(listItemMeinWidget);
    buttonInfo->setFixedSize(25, 25);
    buttonInfo->move(230, 55);
    buttonInfo-> setIcon(QIcon(":/resource/Info_light@3x.png"));
    buttonInfo->setIconSize(QSize(25, 25));
    buttonInfo->show();
    connect(buttonInfo, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonInfo_clicked);

    QPushButton* buttonDelete = new QPushButton(listItemMeinWidget);
    buttonDelete->setFixedSize(25, 25);
    buttonDelete->move(230, 90);
    buttonDelete-> setIcon(QIcon(":/resource/Trash@3x.png"));
    buttonDelete->setIconSize(QSize(25, 25));
    buttonDelete->show();
    buttonDelete->setProperty("imageIndex", index);
    connect(buttonDelete, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonDelete_clicked);


}

void DialogWindowListOfImage::on_ListOfImageMenuBarPlusButton_clicked(){
    int imageId = imageManager->ChooseImageFromFiles(this);
    if (imageId != -1) {  // Перевірте, що ID є дійсним
        CreateListOfImageItem(listItemCordinate_y,imageManager->findImageById(imageId));
    }
}
void DialogWindowListOfImage::on_buttonFullSize_clicked() {
    QString imageUrl = imageManager->GetImageByIndex(sender()->property("imageIndex").toInt()).getUrl();
    QDesktopServices::openUrl(QUrl("file:///" + imageUrl));
}

void DialogWindowListOfImage::on_buttonInfo_clicked() {
    qDebug() << "Info button clicked";
}

void DialogWindowListOfImage::on_buttonDelete_clicked() {
    int index = sender()->property("imageIndex").toInt();
    imageManager->deleteImageByIndex(index);
    qDebug() <<index;
    QLayoutItem *child;
    while ((child = containerWidget->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    CreateListOfImageIntarface();
}

void DialogWindowListOfImage::on_buttonImage_clicked()
{
    int index = sender()->property("imageIndex").toInt();
    emit imageSelected(index);
}
DialogWindowListOfImage::~DialogWindowListOfImage()
{
    delete ui;
}
