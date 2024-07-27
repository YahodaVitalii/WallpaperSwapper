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
#include <QScrollArea>
#include <QCheckBox>
#include "style.h"
#include "imageslist.h"
#include "sqlitedbmanager.h"
#include "uielementfactory.h"


class InterfaceAddition : public QWidget{
    Q_OBJECT

public:
    InterfaceAddition(QWidget *parent, ImagesList* imagesList);
    ~InterfaceAddition();
    QWidget* CreateListOfImageItem(int imageIndex);
    QWidget*  CreateRandomListOfImageItem(int imageIndex);
    QWidget* CreateRandomListOfImageView(const RandomImageList* randomImageList);
    QWidget* CreateWeekListOfImageItem(int imageIndex, QString DayOfWeek);
    QWidget* CreateWeekListOfImageView(const WeekImageList* weekImageList);
    QWidget* CreateDayListOfImageItem(const TimeRangeImage* item);
    QWidget* CreateDayListOfImageView(const DayImageList* dayImageList);

    UIElementFactory* getUiElementFactory();


signals:
    void updateTimeEdit(int id,QTime startTime,QTime endTime);

private:
    ImagesList* imagesList;
    UIElementFactory* uiElementFactory;

    WidgetGeometry standartImageSize={220,110,10,5};
//    void CreateLableWithImage(QWidget* conteinerWidget, int imageIndex, const WidgetGeometry& geometry);
//    void CreateButtonImage(QWidget* conteinerWidget, int index, const WidgetGeometry& geometry);
//    void CreateButtonSetImage(QWidget *conteinerWidget, QString day, const WidgetGeometry& geometry);

//    void CreateButtonInfo(QWidget* conteinerWidget);
//    void CreateButtonDelete(QWidget* conteinerWidget, int index, int width, int hight, int cordinate_x, int cordinate_y);
//    void CreateButtonFullSize(QWidget* conteinerWidget, int index);
//    void CreateButtonEdit(QWidget* conteinerWidget, int id, int width, int hight, int cordinate_x, int cordinate_y);

//    void CreateLableWithText(QWidget* conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y);
//    void CreateToggleButton(QWidget *containerWidget, int id);


//    QTimeEdit* CreateTimeEditor(QWidget *conteinerWidget, int id, int cordinate_x, int cordinate_y);


};

#endif // INTERFACEADDITION_H
