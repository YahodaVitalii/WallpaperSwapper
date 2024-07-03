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
#include "style.h"
#include "imagemanager.h"
#include "sqlitedbmanager.h"
class InterfaceAddition : public QWidget{
    Q_OBJECT
public:
    InterfaceAddition(QWidget *parent, DBManager* dbManageer, ImageManager* imageManager);
    ~InterfaceAddition();
    QWidget* CreateListOfImageItem(int imageIndex);
    QWidget*  CreateRandomListOfImageItem(int imageIndex);
    QWidget* CreateRandomListOfImageView(const RandomImageList* randomImageList);
    QWidget* CreateWeekListOfImageItem(int imageIndex, QString DayOfWeek);
    QWidget* CreateWeekListOfImageView(const WeekImageList* weekImageList);
    QWidget* CreateDayListOfImageItem(const TimeRangeImage* item);
    QWidget* CreateDayListOfImage(const DayImageList* dayImageList);



    //QWidget* getContainerWidgetDWindowImageOfList() const;
    void CreateContainerWidgetDWindowImageOfList();
    void DeleteContainerWidgetDWindowImageOfList();
//    QWidget *getContainerWidgetRandomImageListCreate() const;
//    QWidget *getcontainerWidgetRandomImageListShow() const;
//    QWidget *getcontainerWidgetWeekImageListCreate() const;
//    QWidget *getcontainerWidgetWeekImageListShow() const;
//    QWidget *getcontainerWidgetDayImageListCreate()const;
//    QWidget *getcontainerWidgetDayImageListShow() const;
    void CreateScrollArea(QWidget* parent, QWidget* child, int width, int hight, int cordinate_X, int cordinate_Y);
    void ClearConteinerWidget(QWidget* containerWidget);

    //void setTargetContainer(QWidget *container);
 void setWidgetIntoScrollArea(QWidget* conteinerWidget,QWidget* childWidget);

signals:
    void imageSelected(int index);
    void sendEditSignalToItem(int id);
    void setImageIntoWeekListItem(QString day);
    void updateTimeEdit(int id,QTime startTime,QTime endTime);
private slots:
    void on_buttonFullSize_clicked();
    void on_buttonImage_clicked();
    void on_buttonEdit_clicked();
    void on_ButtonSetImage_clicked();
private:
    void CreateLableWithImage(QWidget* listItemMeinWidget, int index, int cordinate_x, int cordinate_y);
    void CreateButtonInfo(QWidget* listItemMeinWidget);
    void CreateButtonDelete(QWidget* listItemMeinWidget, int index, int width, int hight, int cordinate_x, int cordinate_y);
    void CreateButtonFullSize(QWidget* listItemMeinWidget, int index);
    void CreateButtonImage(QWidget* listItemMeinWidget,int index);

    void CreateButtonTurnOnTurnOff(QWidget* conteinerWidget);
    void CreateLableWithText(QWidget* conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y);
    void CreateButtonEdit(QWidget* conteinerWidget, int id, int width, int hight, int cordinate_x, int cordinate_y);
    void CreateButtonSetImage(QWidget *listItemMeinWidget, QString day,int width, int hight, int cordinate_x, int cordinate_y);
    QTimeEdit* CreateTimeEditor(QWidget *listItemMeinWidget, int id, int cordinate_x, int cordinate_y);


//    QWidget *containerWidgetDWindowImageOfList = nullptr;
//    QWidget *containerWidgetRandomImageListCreate = nullptr;
//    QWidget *containerWidgetRandomImageListShow = nullptr;
//    QWidget *containerWidgetWeekImageListCreate = nullptr;
//    QWidget *containerWidgetWeekImageListShow = nullptr;
//    QWidget* containerWidgetDayImageListCreate =nullptr ;
//    QWidget* containerWidgetDayImageListShow =nullptr ;
    QWidget *parentWidget;
    ImageManager* imageManager;
    DBManager* dbManager;

};

#endif // INTERFACEADDITION_H
