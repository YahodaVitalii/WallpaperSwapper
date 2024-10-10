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
QWidget *InterfaceAddition::BuildRandomListItem(int imageIndex)
{
    QWidget* itemWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    uiElementFactory->CreateButtonFullSize(itemWidget,imageIndex);
    uiElementFactory->CreateButtonDelete(itemWidget,imageIndex,25,25,230,90);
    uiElementFactory->CreateButtonInfo(itemWidget);

    return itemWidget;
}

QWidget *InterfaceAddition::BuildRandomListView(const RandomImageList *randomImageList)
{
    QWidget* viewWidget = CreateContainerWidget();

    uiElementFactory->CreateToggleButton(viewWidget,randomImageList->getId());
    uiElementFactory->CreateLableWithText(viewWidget,randomImageList->getName(),290,65);
    uiElementFactory->CreateLableWithText(viewWidget, randomImageList->getTimeInterval().toString("HH:mm"), 290, 95);
    uiElementFactory->CreateButtonDelete(viewWidget,randomImageList->getId(),35,35,500,70);
    uiElementFactory->CreateButtonEdit(viewWidget,randomImageList->getId(),35,35,500,20);

    imageSlider = new RandomViewImageSlider(randomImageList->getImageIds(), standartImageSize, viewWidget);

    return viewWidget;

}

QWidget *InterfaceAddition::BuildWeekListItem(int imageIndex, DayOfWeek dayOfWeek)
{
    QWidget* itemWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithImage(itemWidget,imageIndex,standartImageSize);
    uiElementFactory->CreateButtonSetImage(itemWidget,static_cast<int>(dayOfWeek),standartImageSize);
    uiElementFactory->CreateLableWithText(itemWidget,dayOfWeekToString(dayOfWeek),290,95);

    return itemWidget;
}

QWidget *InterfaceAddition::BuildWeekListView(const WeekImageList* weekImageList)
{
    QWidget* viewWidget = CreateContainerWidget();
    uiElementFactory->CreateToggleButton(viewWidget,weekImageList->getId());
    uiElementFactory->CreateButtonDelete(viewWidget,weekImageList->getId(),35,35,500,70);
    uiElementFactory->CreateButtonEdit(viewWidget,weekImageList->getId(),35,35,500,20);

    imageSlider = new WeekViewImageSlider(weekImageList->getImages(), standartImageSize, viewWidget);

    return viewWidget;
}

QWidget *InterfaceAddition::BuildDayListItem(const TimeRangeImage* item)
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

QWidget *InterfaceAddition::BuildDayListView(const DayImageList *dayImageList)
{
    QWidget* viewWidget = CreateContainerWidget();

    uiElementFactory->CreateLableWithText(viewWidget,dayImageList->getName(),290,35);
    uiElementFactory->CreateButtonEdit(viewWidget,dayImageList->getId(),35,35,500,20);
    uiElementFactory->CreateButtonDelete(viewWidget,dayImageList->getId(),35,35,500,70);
    uiElementFactory->CreateToggleButton(viewWidget,dayImageList->getId());

   imageSlider = new DayViewImageSlider(dayImageList->getImages(), standartImageSize, viewWidget);

   return viewWidget;
}

QWidget* InterfaceAddition::BuildMoodTabItem(int emodjiID, int imageID)
{
    QWidget* itemWidget = CreateContainerWidget();
    itemWidget->setProperty("WidgetItemId",emodjiID);

    EmodjiTableManager emodjiManager;
    QString emodji = emodjiManager.getEmodjiById(emodjiID);

    // Створюємо віджет з текстом емодзі
    uiElementFactory->CreateLableWithText(itemWidget, emodji, 290, 35);
    uiElementFactory->CreateLableWithImage(itemWidget, imageID, standartImageSize);
    uiElementFactory->CreateButtonSetImage(itemWidget, emodjiID, standartImageSize);

    return itemWidget;
}

QPushButton *InterfaceAddition::CreateEmojiButton(int emojiKey, const QString &emojiText, QWidget *parent)
{
    QPushButton* emojiButton = new QPushButton(emojiText, parent);
      // emojiButton->setFixedSize(50, 50); // Налаштування розміру кнопки
       emojiButton->setStyleSheet(Style::getIterfaceAdditionStyle()); // Налаштування стилю емоджі
       emojiButton->setCursor(Qt::PointingHandCursor);
       emojiButton->setProperty("emojiKey", emojiKey);
       connect(emojiButton, &QPushButton::clicked, uiElementEventHandler, &UIElementEventHandler::on_EmojiButton_clicked);

       return emojiButton;
}

QWidget *InterfaceAddition::CreateContainerWidget()
{
    QWidget* ConteinerWiget = new QWidget();
    ConteinerWiget->setStyleSheet(Style::getIterfaceAdditionStyle());
    ConteinerWiget->setFixedSize(560, 120);

    return ConteinerWiget;
}


