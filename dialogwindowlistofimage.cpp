#include "dialogwindowlistofimage.h"
#include "ui_dialogwindowlistofimage.h"

DialogWindowListOfImage::DialogWindowListOfImage(DBManager* dbManager, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogWindowListOfImage), dbManager(dbManager)
{
    ui->setupUi(this);
    ui->ListOfImageMenuBar->setStyleSheet(Style::getMenuBarStyle());
}

DialogWindowListOfImage::~DialogWindowListOfImage()
{
    delete ui;
    //listItemMeinWidget->hide();
}

void DialogWindowListOfImage::CreateListOfImageIntarface()
{
  int i =0;
}

void DialogWindowListOfImage::CreateListOfImageItem(QString path)
{

    QWidget* listItemMeinWidget = new QWidget(this);
    listItemMeinWidget->setStyleSheet(Style::getImageListStyle()); // Corrected syntax
    listItemMeinWidget->setFixedSize(260, 120);  // Confirm size is adequate

    // Position at top-left corner of the dialog initially
    listItemMeinWidget->move(20, 90);
    listItemMeinWidget->show();

    QLabel* label = new QLabel(listItemMeinWidget);
    label->setStyleSheet("background-color: rgb(0, 225, 0);"); // Corrected syntax and color comment
    label->setFixedSize(220, 110);  // Confirm size is adequate
    label->move(5, 5);
    QPixmap pixmap(path);
           label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
           label->setScaledContents(true);
    label->show();


    QPushButton* buttonFullSize = new QPushButton(listItemMeinWidget);
    buttonFullSize->setFixedSize(25, 25);
    buttonFullSize->move(230, 20);
    buttonFullSize-> setIcon(QIcon(":/resource/Full@3x.png"));
    buttonFullSize->setIconSize(QSize(25, 25));
    buttonFullSize->show();

    QPushButton* buttonInfo = new QPushButton(listItemMeinWidget);
    buttonInfo->setFixedSize(25, 25);
    buttonInfo->move(230, 55);
    buttonInfo-> setIcon(QIcon(":/resource/Info_light@3x.png"));
    buttonInfo->setIconSize(QSize(25, 25));
    buttonInfo->show();

    QPushButton* buttonDelete = new QPushButton(listItemMeinWidget);
    buttonDelete->setFixedSize(25, 25);
    buttonDelete->move(230, 90);
    buttonDelete-> setIcon(QIcon(":/resource/Trash@3x.png"));
    buttonDelete->setIconSize(QSize(25, 25));
    buttonDelete->show();
}

void DialogWindowListOfImage::on_ListOfImageMenuBarPlusButton_clicked(){
    CreateListOfImageIntarface();
}

