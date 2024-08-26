#include "interfaceaddition.h"
InterfaceAddition::InterfaceAddition(QWidget *parent, UIElementEventHandler* uiElementEventHandler): QWidget(parent),uiElementEventHandler(uiElementEventHandler)
{
    imageList = SQLTableImageList::getInstance();
    uiElementFactory = new UIElementFactory(uiElementEventHandler);

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

    uiElementFactory->CreateToggleButton(viewWidget,randomImageList->getId());
    uiElementFactory->CreateLableWithText(viewWidget,randomImageList->getName(),290,65);
    uiElementFactory->CreateLableWithText(viewWidget, randomImageList->getTimeInterval().toString("HH:mm"), 290, 95);
    uiElementFactory->CreateButtonDelete(viewWidget,randomImageList->getId(),35,35,500,70);
    uiElementFactory->CreateButtonEdit(viewWidget,randomImageList->getId(),35,35,500,20);

    imageSlider = new RandomViewImageSlider(randomImageList->imageIds, standartImageSize, viewWidget);

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
    uiElementFactory->CreateToggleButton(viewWidget,weekImageList->getId());
    uiElementFactory->CreateButtonDelete(viewWidget,weekImageList->getId(),35,35,500,70);
    uiElementFactory->CreateButtonEdit(viewWidget,weekImageList->getId(),35,35,500,20);

    imageSlider = new WeekViewImageSlider(weekImageList->images, standartImageSize, viewWidget);

    return viewWidget;
}

QWidget *InterfaceAddition::BuildDayListOfImageItem(const TimeRangeImage* item)
{
    QWidget* itemWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(itemWidget, item->imageId, standartImageSize);
    uiElementFactory->CreateLableWithText(itemWidget, "from", 245, 10);
    uiElementFactory->CreateLableWithText(itemWidget, "to", 370, 10);

    QTime startTime = QTime::fromString(item->startTime, "HH:mm"); // Передбачимо, що час зберігається в форматі "HH:mm"
    QTime endTime = QTime::fromString(item->endTime, "HH:mm");

    QTimeEdit* startTimeEdit = uiElementFactory->CreateTimeEditor(itemWidget, 290, 10 ,startTime);
    QTimeEdit* endTimeEdit = uiElementFactory->CreateTimeEditor(itemWidget, 390, 10 ,endTime);

    int itemId = item->id;

    connect(startTimeEdit, &QTimeEdit::timeChanged, this, [=](const QTime& time) {
        updateTimeEdit(itemId, time, endTimeEdit->time());
        qDebug() << itemId;
    });

    connect(endTimeEdit, &QTimeEdit::timeChanged, this, [=](const QTime& time) {
        updateTimeEdit(itemId, startTimeEdit->time(), time);
    });



    return itemWidget;
}

QWidget *InterfaceAddition::BuildDayListOfImageView(const DayImageList *dayImageList)
{
    QWidget* viewWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithText(viewWidget,dayImageList->getName(),290,35);
    uiElementFactory->CreateButtonEdit(viewWidget,dayImageList->getId(),35,35,500,20);
    uiElementFactory->CreateButtonDelete(viewWidget,dayImageList->getId(),35,35,500,70);
    uiElementFactory->CreateToggleButton(viewWidget,dayImageList->getId());

   imageSlider = new DayViewImageSlider(dayImageList->images, standartImageSize, viewWidget);

    return viewWidget;
}

QWidget *InterfaceAddition::CreateContainerWidget()
{
    QWidget* ConteinerWiget = new QWidget();
    ConteinerWiget->setStyleSheet(Style::getIterfaceAdditionStyle());
    ConteinerWiget->setFixedSize(560, 120);

    return ConteinerWiget;
}


