#ifndef INTERFACEADDITION_H
#define INTERFACEADDITION_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimeEdit>
#include <QDesktopServices>
#include <QTabWidget>
#include <QScrollArea>
#include <QCheckBox>
#include "GUI/style/style.h"
#include "models/imagelist.h"
#include "uielementfactory.h"
#include "models/sqltableimagelist.h"
#include "GUI/CustomWidgets/sliders/randomviewimageslider.h"
#include "GUI/CustomWidgets/sliders/weekviewimageslider.h"
#include "GUI/CustomWidgets/sliders/dayviewimageslider.h"
#include "DB/TablesManagers/emodjitablemanager.h"
#include "models/weekimagelist.h"
#include "models/randomimagelist.h"


class InterfaceAddition : public QWidget{
    Q_OBJECT

public:
    InterfaceAddition(QWidget *parent, UIElementEventHandler *uiElementEventHandler);
    ~InterfaceAddition();
    QWidget* BuildListOfImageItem(int imageIndex);
    QWidget* BuildRandomListItem(int imageIndex);
    QWidget* BuildRandomListView(const RandomImageList* randomImageList);
    QWidget* BuildWeekListItem(int imageIndex, DayOfWeek dayOfWeek);
    QWidget* BuildWeekListView(const WeekImageList* weekImageList);
    QWidget* BuildDayListItem(const TimeRangeImage* item);
    QWidget* BuildDayListView(const DayImageList* dayImageList);
    QWidget* BuildMoodTabItem(int emodjiID, int imageID);
    QPushButton *CreateEmojiButton(int emojiKey,const QString& emojiText, QWidget* parent);

private:
    QWidget *CreateContainerWidget();
signals:
    void updateTimeEdit(int id,QTime startTime,QTime endTime);

private:
    ImageList* imageList;
    UIElementFactory* uiElementFactory;
    UIElementEventHandler *uiElementEventHandler;
    ImageSlider* imageSlider ;
    const WidgetGeometry standartImageSize={220,110,10,5};




};

#endif // INTERFACEADDITION_H
