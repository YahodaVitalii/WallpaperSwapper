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
#include "style.h"
#include "imagelist.h"
#include "sqlitedbmanager.h"
#include "uielementfactory.h"
#include "sqltableimagelist.h"


class InterfaceAddition : public QWidget{
    Q_OBJECT

public:
    InterfaceAddition(QWidget *parent, UIElementEventHandler *uiElementEventHandler);
    ~InterfaceAddition();
    QWidget* BuildListOfImageItem(int imageIndex);
    QWidget* BuildRandomListOfImageItem(int imageIndex);
    QWidget* BuildRandomListOfImageView(const RandomImageList* randomImageList);
    QWidget* BuildWeekListOfImageItem(int imageIndex, QString DayOfWeek);
    QWidget* BuildWeekListOfImageView(const WeekImageList* weekImageList);
    QWidget* BuildDayListOfImageItem(const TimeRangeImage* item);
    QWidget* BuildDayListOfImageView(const DayImageList* dayImageList);
private:
    QWidget *CreateContainerWidget();
signals:
    void updateTimeEdit(int id,QTime startTime,QTime endTime);

private:
    ImageList* imageList;
    UIElementFactory* uiElementFactory;
    UIElementEventHandler *uiElementEventHandler;
    const WidgetGeometry standartImageSize={220,110,10,5};




};

#endif // INTERFACEADDITION_H
