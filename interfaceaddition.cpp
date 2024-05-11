#include "interfaceaddition.h"

InterfaceAddition::InterfaceAddition(QWidget *parent, DBManager* dbManager, ImageManager *imageManager): QWidget(parent),dbManager(dbManager),imageManager(imageManager)
{
    containerWidgetDWindowImageOfList = new QWidget();
       containerWidgetRandomImageListCreate = new QWidget();


    QVBoxLayout *layout1 = new QVBoxLayout(containerWidgetDWindowImageOfList);
    containerWidgetDWindowImageOfList->setLayout(layout1);
    QVBoxLayout *layout2 = new QVBoxLayout(containerWidgetRandomImageListCreate);
    containerWidgetRandomImageListCreate->setLayout(layout2);

}

InterfaceAddition::~InterfaceAddition()
{
        delete containerWidgetDWindowImageOfList;
        delete containerWidgetRandomImageListCreate;
}

void InterfaceAddition::CreateListOfImageItem( int index)
{
    QWidget* listItemMeinWidget = new QWidget();
    listItemMeinWidget->setStyleSheet(Style::getImageListStyle());
    listItemMeinWidget->setFixedSize(260, 120);

    setWidgetIntoScrollArea(containerWidgetDWindowImageOfList,listItemMeinWidget);
    //listItemMeinWidget->move(20, listItemCordinate_y);


    listItemMeinWidget->show();

    CreateLableWithImage(listItemMeinWidget,index);
    CreateButtonImage(listItemMeinWidget,index);
    CreateButtonFullSize(listItemMeinWidget,index);
    CreateButtonDelete(listItemMeinWidget,index);
    CreateButtonInfo(listItemMeinWidget);


}

void InterfaceAddition::CreateLableWithImage(QWidget *listItemMeinWidget, int index)
{
    QLabel* label = new QLabel(listItemMeinWidget);
    //label->setStyleSheet("background-color: rgb(0, 225, 0);");
    label->setFixedSize(220, 110);
    label->move(5, 5);
//qDebug()<<index;
    QPixmap pixmap(imageManager->GetImageByIndex(index).getUrl());

    label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
    label->setScaledContents(true);
    label->show();
}

void InterfaceAddition::CreateButtonInfo(QWidget *listItemMeinWidget)
{
    QPushButton* buttonInfo = new QPushButton(listItemMeinWidget);
    buttonInfo->setFixedSize(25, 25);
    buttonInfo->move(230, 55);
    buttonInfo-> setIcon(QIcon(":/resource/Info_light@3x.png"));
    buttonInfo->setIconSize(QSize(25, 25));
    buttonInfo->show();
    // connect(buttonInfo, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonInfo_clicked);
}

void InterfaceAddition::CreateButtonDelete(QWidget *listItemMeinWidget,int index)
{
    QPushButton* buttonDelete = new QPushButton(listItemMeinWidget);
    buttonDelete->setFixedSize(25, 25);
    buttonDelete->move(230, 90);
    buttonDelete-> setIcon(QIcon(":/resource/Trash@3x.png"));
    buttonDelete->setIconSize(QSize(25, 25));
    buttonDelete->show();
    buttonDelete->setProperty("imageIndex", index);
    // connect(buttonDelete, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonDelete_clicked);
}

void InterfaceAddition::CreateButtonFullSize(QWidget *listItemMeinWidget,int index)
{
    QPushButton* buttonFullSize = new QPushButton(listItemMeinWidget);
    buttonFullSize->setFixedSize(25, 25);
    buttonFullSize->move(230, 20);
    buttonFullSize-> setIcon(QIcon(":/resource/Full@3x.png"));
    buttonFullSize->setIconSize(QSize(25, 25));
    buttonFullSize->show();
    buttonFullSize->setProperty("imageIndex", index);
     connect(buttonFullSize, &QPushButton::clicked, this, &InterfaceAddition::on_buttonFullSize_clicked);
}

void InterfaceAddition::CreateButtonImage(QWidget *listItemMeinWidget, int index)
{
    QPushButton* buttonImage = new QPushButton(listItemMeinWidget);
    buttonImage->setObjectName("buttonImage");  // Встановлення об'єктного імені
    buttonImage->setFixedSize(220, 110);
    buttonImage->move(5, 5);
    buttonImage->show();
    buttonImage->setProperty("imageIndex", index);
    connect(buttonImage, &QPushButton::clicked, this, &InterfaceAddition::on_buttonImage_clicked);
}

void InterfaceAddition::setWidgetIntoScrollArea(QWidget *conteinerWidget, QWidget *childWidget)
{
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(conteinerWidget->layout());
    layout->addWidget(childWidget);
}

void InterfaceAddition::CreateRandomListOfImageItem(int index)
{
    QWidget* RandomListItemMeinWidget = new QWidget();
    RandomListItemMeinWidget->setStyleSheet(Style::getImageListStyle());
    RandomListItemMeinWidget->setFixedSize(260, 120);

    setWidgetIntoScrollArea(containerWidgetRandomImageListCreate,RandomListItemMeinWidget);
    //listItemMeinWidget->move(20, listItemCordinate_y);


    RandomListItemMeinWidget->show();

    CreateLableWithImage(RandomListItemMeinWidget,index);
    CreateButtonImage(RandomListItemMeinWidget,index);
    CreateButtonFullSize(RandomListItemMeinWidget,index);
    CreateButtonDelete(RandomListItemMeinWidget,index);
    CreateButtonInfo(RandomListItemMeinWidget);
}

QWidget* InterfaceAddition::getContainerWidgetDWindowImageOfList() const
{
    return containerWidgetDWindowImageOfList;
}

void InterfaceAddition::CreateContainerWidgetDWindowImageOfList()
{
containerWidgetDWindowImageOfList =  new QWidget();
}

void InterfaceAddition::DeleteContainerWidgetDWindowImageOfList()
{
 delete containerWidgetDWindowImageOfList;
    containerWidgetDWindowImageOfList = nullptr;
}

QWidget *InterfaceAddition::getContainerWidgetRandomImageListCreate() const
{
    return containerWidgetRandomImageListCreate;
}

void InterfaceAddition::CreateScrollArea(QWidget *parent, QWidget *child,int width,int hight,int cordinate_X, int cordinate_Y)
{

    QScrollArea* scrollArea = new QScrollArea(parent);
        scrollArea->setFixedSize(width, hight);
        scrollArea->move(cordinate_X, cordinate_Y);
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(child);
}
void InterfaceAddition::ClearConteinerWidget(QWidget *containerWidget)
{
    QLayoutItem *child;
        while ((child = containerWidget->layout()->takeAt(0)) != nullptr) {
            delete child->widget();
            delete child;
        }
}

//void InterfaceAddition::setTargetContainer(QWidget *container) {
//    containerWidget = container;

//    // Призначте новий макет для нового контейнера
//    if (!containerWidget->layout()) {
//        QVBoxLayout *newLayout = new QVBoxLayout(containerWidget);
//        containerWidget->setLayout(newLayout);
//    }
//}
void InterfaceAddition::on_buttonFullSize_clicked()
{
    QString imageUrl = imageManager->GetImageByIndex(sender()->property("imageIndex").toInt()).getUrl();
    QDesktopServices::openUrl(QUrl("file:///" + imageUrl));

}

void InterfaceAddition::on_buttonImage_clicked() {
    int index = sender()->property("imageIndex").toInt();
    emit imageSelected(index);  // Сигнал передає індекс зображення
    //qDebug()<<index;
}

