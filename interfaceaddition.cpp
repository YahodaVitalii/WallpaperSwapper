#include "interfaceaddition.h"

InterfaceAddition::InterfaceAddition(QWidget *parent, DBManager* dbManager, ImageManager *imageManager): QWidget(parent),dbManager(dbManager),imageManager(imageManager)
{
    containerWidgetDWindowImageOfList = new QWidget();
       containerWidgetRandomImageListCreate = new QWidget();
        containerWidgetRandomImageListShow  = new QWidget();

    QVBoxLayout *layout1 = new QVBoxLayout(containerWidgetDWindowImageOfList);
    containerWidgetDWindowImageOfList->setLayout(layout1);
    QVBoxLayout *layout2 = new QVBoxLayout(containerWidgetRandomImageListCreate);
    containerWidgetRandomImageListCreate->setLayout(layout2);
    QVBoxLayout *layout3 = new QVBoxLayout(containerWidgetRandomImageListShow);
    containerWidgetRandomImageListShow->setLayout(layout3);

}

InterfaceAddition::~InterfaceAddition()
{
//        delete containerWidgetDWindowImageOfList;
//        delete containerWidgetRandomImageListCreate;
//        delete containerWidgetRandomImageListShow;
}

void InterfaceAddition::CreateListOfImageItem( int index)
{
    QWidget* listItemMeinWidget = new QWidget();
    listItemMeinWidget->setStyleSheet(Style::getImageListStyle());
    listItemMeinWidget->setFixedSize(260, 120);

    setWidgetIntoScrollArea(containerWidgetDWindowImageOfList,listItemMeinWidget);
    //listItemMeinWidget->move(20, listItemCordinate_y);


    listItemMeinWidget->show();

    CreateLableWithImage(listItemMeinWidget,index,5,5);
    CreateButtonImage(listItemMeinWidget,index);
    CreateButtonFullSize(listItemMeinWidget,index);
    CreateButtonDelete(listItemMeinWidget,index,25,25,230,90);
    CreateButtonInfo(listItemMeinWidget);


}
void InterfaceAddition::CreateRandomListOfImageItem(int index)
{
    QWidget* RandomListItemMeinWidget = new QWidget();
    RandomListItemMeinWidget->setStyleSheet(Style::getImageListStyle());
    RandomListItemMeinWidget->setFixedSize(310, 120);
    //RandomListItemMeinWidget->move(100,0);




    RandomListItemMeinWidget->setStyleSheet(Style::getIterfaceAdditionStyle());
    setWidgetIntoScrollArea(containerWidgetRandomImageListCreate,RandomListItemMeinWidget);
    CreateLableWithImage(RandomListItemMeinWidget,index,10,5);
    CreateButtonFullSize(RandomListItemMeinWidget,index);
    CreateButtonDelete(RandomListItemMeinWidget,index,25,25,230,90);
    CreateButtonInfo(RandomListItemMeinWidget);
}

void InterfaceAddition::CreateRandomListOfImageView(int index, int id, QString name, QString time)
{
    QWidget* RandomListViewItemMeinWidget = new QWidget();
    RandomListViewItemMeinWidget->setStyleSheet(Style::getIterfaceAdditionStyle());
    RandomListViewItemMeinWidget->setFixedSize(560, 120);
    setWidgetIntoScrollArea(containerWidgetRandomImageListShow,RandomListViewItemMeinWidget);
    RandomListViewItemMeinWidget->show();
    CreateLableWithImage(RandomListViewItemMeinWidget,index,15,5);
    CreateButtonTurnOnTurnOff(RandomListViewItemMeinWidget);
    CreateLableWithText(RandomListViewItemMeinWidget,name,290,65);
     CreateLableWithText(RandomListViewItemMeinWidget,time,290,95);
     CreateButtonDelete(RandomListViewItemMeinWidget,index,35,35,500,70);
     CreateButtonEdit(RandomListViewItemMeinWidget,id,35,35,500,20);

}
void InterfaceAddition::CreateLableWithImage(QWidget *listItemMeinWidget, int index, int cordinate_x, int cordinate_y)
{
    QLabel* label = new QLabel(listItemMeinWidget);
    //label->setStyleSheet("background-color: rgb(0, 225, 0);");
    label->setFixedSize(220, 110);
    label->move(cordinate_x, cordinate_y);
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

void InterfaceAddition::CreateButtonDelete(QWidget *listItemMeinWidget,int index,int width,int hight,int cordinate_x,int cordinate_y)
{
    QPushButton* buttonDelete = new QPushButton(listItemMeinWidget);
    buttonDelete->setFixedSize(width, hight);
    buttonDelete->move(cordinate_x, cordinate_y);
    buttonDelete-> setIcon(QIcon(":/resource/Trash@3x.png"));
    buttonDelete->setIconSize(QSize(width, hight));
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

void InterfaceAddition::CreateButtonTurnOnTurnOff(QWidget *conteinerWidget)
{
    QWidget* containerWidgetForButtons = new QWidget(conteinerWidget);
    containerWidgetForButtons->setFixedSize(160, 40);
    containerWidgetForButtons->setStyleSheet(Style::getOnOffButtonStyle());
    containerWidgetForButtons->move(290, 15);
    containerWidgetForButtons->show();

    QPushButton* ButtonOn = new QPushButton(containerWidgetForButtons);
    ButtonOn->setFixedSize(80, 40);
    ButtonOn->setText("On");
    ButtonOn->move(0, 0); // Встановіть позицію кнопки в межах її батьківського віджета
    ButtonOn->show();

    QPushButton* ButtonOff = new QPushButton(containerWidgetForButtons);
    ButtonOff->setFixedSize(80, 40);
   // ButtonOff->setStyleSheet(Style::getOnOffButtonStyle());
    ButtonOff->setText("Off");
    ButtonOff->move(80, 0); // Встановіть позицію кнопки в межах її батьківського віджета
    ButtonOff->show();
}

void InterfaceAddition::CreateLableWithText(QWidget *conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y)
{
    QLabel* labelText = new QLabel(conteinerWidget);
    labelText->setText(TextOfLabel);
    labelText->move(Cordinate_x,Cordinate_y);
    labelText->show();
}

void InterfaceAddition::CreateButtonEdit(QWidget *conteinerWidget, int id, int width, int hight, int cordinate_x, int cordinate_y)
{
    QPushButton* buttonEdit = new QPushButton(conteinerWidget);
    buttonEdit->setFixedSize(width, hight);
    buttonEdit->move(cordinate_x, cordinate_y);
    buttonEdit-> setIcon(QIcon(":/resource/Edit_fill@3x.png"));
    buttonEdit->setIconSize(QSize(width, hight));
    buttonEdit->show();
    buttonEdit->setProperty("ListId", id);
     connect(buttonEdit, &QPushButton::clicked, this, &InterfaceAddition::on_buttonEdit_clicked);
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

QWidget *InterfaceAddition::getcontainerWidgetRandomImageListShow() const
{
   return containerWidgetRandomImageListShow;
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
}

void InterfaceAddition::on_buttonEdit_clicked()
{
      emit randomImageListEditSignal(sender()->property("ListId").toInt());
}

