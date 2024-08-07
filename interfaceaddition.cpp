#include "interfaceaddition.h"

InterfaceAddition::InterfaceAddition(QWidget *parent, UIElementFactory *uiElementFactory): QWidget(parent),uiElementFactory(uiElementFactory)
{
    imageList = SQLTableImageList::getInstance();
}

InterfaceAddition::~InterfaceAddition()
{
}
QWidget *InterfaceAddition::BuildListOfImageItem(int imageIndex)
{
    QWidget* itemWidget = new QWidget();
    itemWidget->setStyleSheet(Style::getImageListStyle());
    itemWidget->setFixedSize(260, 120);

    uiElementFactory->CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    uiElementFactory->CreateButtonImage(itemWidget,imageIndex,standartImageSize);
    uiElementFactory->CreateButtonFullSize(itemWidget,imageIndex);
    uiElementFactory->CreateButtonDelete(itemWidget,imageIndex,25,25,230,90);
    uiElementFactory->CreateButtonInfo(itemWidget);

    return itemWidget;
}
QWidget *InterfaceAddition::BuildRandomListOfImageItem(int imageIndex)
{
    QWidget* itemWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    uiElementFactory->CreateButtonFullSize(itemWidget,imageIndex);
    uiElementFactory->CreateButtonDelete(itemWidget,imageIndex,25,25,230,90);
    uiElementFactory->CreateButtonInfo(itemWidget);

    return itemWidget;
}

QWidget *InterfaceAddition::BuildRandomListOfImageView(const RandomImageList *randomImageList)
{
    QWidget* viewWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(viewWidget,imageList->findImageById(randomImageList->imageIds[0]),standartImageSize);
    uiElementFactory->CreateToggleButton(viewWidget,randomImageList->getId());
    uiElementFactory->CreateLableWithText(viewWidget,randomImageList->getName(),290,65);
    uiElementFactory->CreateLableWithText(viewWidget,randomImageList->getTimeInterval().toString(),290,95);
    uiElementFactory->CreateButtonDelete(viewWidget,randomImageList->getId(),35,35,500,70);
    uiElementFactory->CreateButtonEdit(viewWidget,randomImageList->getId(),35,35,500,20);

    return viewWidget;

}

QWidget *InterfaceAddition::BuildWeekListOfImageItem(int imageIndex, QString DayOfWeek)
{
    QWidget* itemWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    uiElementFactory->CreateButtonSetImage(itemWidget,DayOfWeek,standartImageSize);
    uiElementFactory->CreateLableWithText(itemWidget,DayOfWeek,290,95);

    return itemWidget;
}

QWidget *InterfaceAddition::BuildWeekListOfImageView(const WeekImageList* weekImageList)
{
    QWidget* viewWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(viewWidget,weekImageList->images["Other days"],standartImageSize);
    uiElementFactory->CreateLableWithText(viewWidget,weekImageList->getName(),290,65);
    uiElementFactory->CreateToggleButton(viewWidget,weekImageList->getId());
    uiElementFactory->CreateButtonDelete(viewWidget,weekImageList->getId(),35,35,500,70);
    uiElementFactory->CreateButtonEdit(viewWidget,weekImageList->getId(),35,35,500,20);

    return viewWidget;
}

QWidget *InterfaceAddition::BuildDayListOfImageItem(const TimeRangeImage* item)
{
    QWidget* itemWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(itemWidget,item->imageId,standartImageSize);
    uiElementFactory->CreateLableWithText(itemWidget,"from",245,10);
    uiElementFactory->CreateLableWithText(itemWidget,"to",370,10);

    QTimeEdit* startTimeEdit = uiElementFactory->CreateTimeEditor(itemWidget,item->id,290,10);
    QTimeEdit* endTimeEdit = uiElementFactory->CreateTimeEditor(itemWidget,item->id,390,10);
    connect(startTimeEdit, &QTimeEdit::timeChanged, this, [=](const QTime& time) {
        updateTimeEdit(item->id, time, endTimeEdit->time());
    });

    connect(endTimeEdit, &QTimeEdit::timeChanged, this, [=](const QTime& time) {
        updateTimeEdit(item->id, startTimeEdit->time(), time);
    });

    return itemWidget;
}

QWidget *InterfaceAddition::BuildDayListOfImageView(const DayImageList *dayImageList)
{
    QWidget* viewWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(viewWidget,dayImageList->images[0].imageId,standartImageSize);
    uiElementFactory->CreateLableWithText(viewWidget,dayImageList->getName(),290,35);
    uiElementFactory->CreateLableWithText(viewWidget,dayImageList->images[0].startTime + dayImageList->images[0].endTime,290,75);
    uiElementFactory->CreateButtonEdit(viewWidget,dayImageList->getId(),35,35,500,20);
    uiElementFactory->CreateButtonDelete(viewWidget,dayImageList->getId(),35,35,500,70);
    uiElementFactory->CreateToggleButton(viewWidget,dayImageList->getId());

    return viewWidget;
}

QWidget *InterfaceAddition::CreateContainerWidget()
{
    QWidget* ConteinerWiget = new QWidget();
    ConteinerWiget->setStyleSheet(Style::getIterfaceAdditionStyle());
    ConteinerWiget->setFixedSize(560, 120);

    return ConteinerWiget;
}


