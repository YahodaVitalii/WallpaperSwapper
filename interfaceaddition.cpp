#include "interfaceaddition.h"

InterfaceAddition::InterfaceAddition(QWidget *parent, ImagesList *imageManager): QWidget(parent),imageManager(imageManager)
{

}

InterfaceAddition::~InterfaceAddition()
{

}

QWidget *InterfaceAddition::CreateListOfImageItem(int imageIndex)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setStyleSheet(Style::getImageListStyle());
    itemWidget->setFixedSize(260, 120);

    CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    CreateButtonImage(itemWidget,imageIndex,standartImageSize);
    CreateButtonFullSize(itemWidget,imageIndex);
    CreateButtonDelete(itemWidget,imageIndex,25,25,230,90);
    CreateButtonInfo(itemWidget);

    return itemWidget;
}
QWidget *InterfaceAddition::CreateRandomListOfImageItem(int imageIndex)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setStyleSheet(Style::getImageListStyle());
    itemWidget->setFixedSize(310, 120);
    itemWidget->setStyleSheet(Style::getIterfaceAdditionStyle());

    CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    CreateButtonFullSize(itemWidget,imageIndex);
    CreateButtonDelete(itemWidget,imageIndex,25,25,230,90);
    CreateButtonInfo(itemWidget);

    return itemWidget;
}

QWidget *InterfaceAddition::CreateRandomListOfImageView(const RandomImageList *randomImageList)
{
    QWidget* viewWidget = new QWidget();
    viewWidget->setStyleSheet(Style::getIterfaceAdditionStyle());
    viewWidget->setFixedSize(560, 120);

    CreateLableWithImage(viewWidget,imageManager->findImageById(randomImageList->imageIds[0]),standartImageSize);
    CreateToggleButton(viewWidget,randomImageList->getId());
    CreateLableWithText(viewWidget,randomImageList->getName(),290,65);
    CreateLableWithText(viewWidget,randomImageList->getTimeInterval().toString(),290,95);
    CreateButtonDelete(viewWidget,randomImageList->getId(),35,35,500,70);
    CreateButtonEdit(viewWidget,randomImageList->getId(),35,35,500,20);

    return viewWidget;

}

QWidget *InterfaceAddition::CreateWeekListOfImageItem(int imageIndex, QString DayOfWeek)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setStyleSheet(Style::getIterfaceAdditionStyle());
    itemWidget->setFixedSize(560, 120);

    CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    CreateButtonSetImage(itemWidget,DayOfWeek,standartImageSize);
    CreateLableWithText(itemWidget,DayOfWeek,290,95);

 return itemWidget;
}

QWidget *InterfaceAddition::CreateWeekListOfImageView(const WeekImageList* weekImageList)
{

    QWidget* viewWidget = new QWidget();
    viewWidget->setStyleSheet(Style::getIterfaceAdditionStyle());
    viewWidget->setFixedSize(560, 120);

    CreateLableWithImage(viewWidget,weekImageList->images["Other days"],standartImageSize);
    CreateLableWithText(viewWidget,weekImageList->getName(),290,65);
    CreateToggleButton(viewWidget,weekImageList->getId());
    CreateButtonDelete(viewWidget,weekImageList->getId(),35,35,500,70);
    CreateButtonEdit(viewWidget,weekImageList->getId(),35,35,500,20);

    return viewWidget;
}

QWidget *InterfaceAddition::CreateDayListOfImageItem(const TimeRangeImage* item)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setStyleSheet(Style::getIterfaceAdditionStyle());
    itemWidget->setFixedSize(560, 120);

    CreateLableWithImage(itemWidget,item->imageId,standartImageSize);
    CreateLableWithText(itemWidget,"from",245,10);
    CreateLableWithText(itemWidget,"to",370,10);

    QTimeEdit* startTimeEdit = CreateTimeEditor(itemWidget,item->id,290,10);
    QTimeEdit* endTimeEdit = CreateTimeEditor(itemWidget,item->id,390,10);
    connect(startTimeEdit, &QTimeEdit::timeChanged, this, [=](const QTime& time) {
        updateTimeEdit(item->id, time, endTimeEdit->time());
    });

    connect(endTimeEdit, &QTimeEdit::timeChanged, this, [=](const QTime& time) {
        updateTimeEdit(item->id, startTimeEdit->time(), time);
    });

    return itemWidget;
}

QWidget *InterfaceAddition::CreateDayListOfImageView(const DayImageList *dayImageList)
{

    QWidget* viewWidget = new QWidget();
    viewWidget->setStyleSheet(Style::getIterfaceAdditionStyle());
    viewWidget->setFixedSize(560, 120);

    CreateLableWithImage(viewWidget,dayImageList->images[0].imageId,standartImageSize);
    CreateLableWithText(viewWidget,dayImageList->getName(),290,35);
    CreateLableWithText(viewWidget,dayImageList->images[0].startTime + dayImageList->images[0].endTime,290,75);
    CreateButtonEdit(viewWidget,dayImageList->getId(),35,35,500,20);
    CreateButtonDelete(viewWidget,dayImageList->getId(),35,35,500,70);
    CreateToggleButton(viewWidget,dayImageList->getId());

    return viewWidget;
}
void InterfaceAddition::CreateLableWithImage(QWidget *containerWidget, int imageIndex, const WidgetGeometry &geometry)
{
    QLabel* label = new QLabel(containerWidget);
    label->setFixedSize(geometry.width, geometry.height);
    label->move(geometry.xPos, geometry.yPos);
    if (imageIndex >= 0 && imageIndex < imageManager->getsizeOfImages()) // Check for valid index range
    {
        QPixmap pixmap(imageManager->GetImageByIndex(imageIndex).getUrl());
        label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
    }
    label->setScaledContents(true);
    label->show();
}

void InterfaceAddition::CreateButtonInfo(QWidget *conteinerWidget)
{
    QPushButton* buttonInfo = new QPushButton(conteinerWidget);
    buttonInfo->setFixedSize(25, 25);
    buttonInfo->move(230, 55);
    buttonInfo-> setIcon(QIcon(":/resource/Info_light@3x.png"));
    buttonInfo->setIconSize(QSize(25, 25));
    buttonInfo->show();
    // connect(buttonInfo, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonInfo_clicked);
}

void InterfaceAddition::CreateButtonDelete(QWidget *conteinerWidget, int index, int width, int hight, int cordinate_x, int cordinate_y)
{
    QPushButton* buttonDelete = new QPushButton(conteinerWidget);
    buttonDelete->setFixedSize(width, hight);
    buttonDelete->move(cordinate_x, cordinate_y);
    buttonDelete-> setIcon(QIcon(":/resource/Trash@3x.png"));
    buttonDelete->setIconSize(QSize(width, hight));
    buttonDelete->show();
    buttonDelete->setProperty("imageIndex", index);
    // connect(buttonDelete, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonDelete_clicked);
}

void InterfaceAddition::CreateButtonFullSize(QWidget *conteinerWidget, int index)
{
    QPushButton* buttonFullSize = new QPushButton(conteinerWidget);
    buttonFullSize->setFixedSize(25, 25);
    buttonFullSize->move(230, 20);
    buttonFullSize-> setIcon(QIcon(":/resource/Full@3x.png"));
    buttonFullSize->setIconSize(QSize(25, 25));
    buttonFullSize->show();
    buttonFullSize->setProperty("imageIndex", index);
    connect(buttonFullSize, &QPushButton::clicked, this, &InterfaceAddition::on_buttonFullSize_clicked);
}

void InterfaceAddition::CreateButtonImage(QWidget *conteinerWidget, int index, const WidgetGeometry &geometry)
{
    QPushButton* buttonImage = new QPushButton(conteinerWidget);
    buttonImage->setObjectName("buttonImage");  // Встановлення об'єктного імені
    buttonImage->setFixedSize(geometry.width, geometry.height);
    buttonImage->move(geometry.xPos, geometry.yPos);
    buttonImage->show();
    buttonImage->setProperty("imageIndex", index);
    connect(buttonImage, &QPushButton::clicked, this, &InterfaceAddition::on_buttonImage_clicked);
}




void InterfaceAddition::CreateLableWithText(QWidget *conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y)
{
    QLabel* labelText = new QLabel(conteinerWidget);
    labelText->setText(TextOfLabel);
    labelText->move(Cordinate_x,Cordinate_y);
    labelText->show();
}

void InterfaceAddition::CreateToggleButton(QWidget *containerWidget, int id)
{
    QCheckBox* checkBox = new QCheckBox(containerWidget);
       //checkBox->setFixedSize(10, 10);
       checkBox->move(230, 10);
       checkBox->setProperty("CheckBoxId", id);
       checkBox->show();
       //connect(checkBox, &QCheckBox::stateChanged, this, &InterfaceAddition::on_checkBox_stateChanged);
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

void InterfaceAddition::CreateButtonSetImage(QWidget *conteinerWidget, QString day, const WidgetGeometry& geometry)
{
    QPushButton* ButtonSetImage = new QPushButton(conteinerWidget);
    ButtonSetImage->setObjectName("buttonImage");  // Встановлення об'єктного імені
    ButtonSetImage->setFixedSize(geometry.width, geometry.height);
    ButtonSetImage->move(geometry.xPos, geometry.yPos);
    ButtonSetImage-> setIcon(QIcon(":/resource/Img_load_box_fill@3x.png"));
    ButtonSetImage->setIconSize(QSize(40, 40));
    ButtonSetImage->show();
    ButtonSetImage->setProperty("DayOfButton", day);
    connect(ButtonSetImage, &QPushButton::clicked, this, &InterfaceAddition::on_ButtonSetImage_clicked);
}

QTimeEdit* InterfaceAddition::CreateTimeEditor(QWidget *conteinerWidget, int id, int cordinate_x, int cordinate_y)
{
    QTimeEdit* TimeEdit = new QTimeEdit(conteinerWidget);
    TimeEdit->setFixedSize(70,30);
    TimeEdit->move(cordinate_x, cordinate_y);
    TimeEdit->setProperty("id",id);
    TimeEdit->show();
    return TimeEdit;
}

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
    int elementId = sender()->property("ListId").toInt();
    emit sendEditSignalToItem(elementId);
}

void InterfaceAddition::on_ButtonSetImage_clicked()
{
    QString day = sender()->property("DayOfButton").toString();
    emit setImageIntoWeekListItem(day);  // Сигнал передає індекс зображення
}

