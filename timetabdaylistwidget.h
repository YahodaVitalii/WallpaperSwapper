#ifndef TIMETABDAYLISTWIDGET_H
#define TIMETABDAYLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imageslist.h"
#include "dialogwindowlistofimage.h"
#include "dbdaylisttablemanager.h"
namespace Ui {
class TimeTabDayListWidget;
}

class TimeTabDayListWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::TimeTabDayListWidget *ui;
    DialogWindowListOfImage* dialogWindowListOfImage;
    QWidget *scrollAreaConterinerCreateTab;
    QWidget *scrollAreaConterinerViewTab;

    DBManager* dbManager;
    ImagesList *imagesList;
    InterfaceAddition* interfaceAddition;
    ScrollAreaManager* scrollAreaManager;
    DBDayListTableManager dbDayListTableManager;

    DayImageList* currentDayImageList;
    QVector<DayImageList> DayImageLists;
    QVector<TimeRangeImage> currentImageIds;

public:
    explicit TimeTabDayListWidget(DBManager* dbManager, ImagesList *imagesList, DialogWindowListOfImage *dialogWindowListOfImage, QWidget *parent = nullptr);
    ~TimeTabDayListWidget();

    void SetTimeTabDayListWidgetStyle();
    void CreateViewTabInterface();
    void CreatInterfaceCreateTab();
    void UpdateViewTabItem();
    void AddNewDayList();
    void SetScrollAreaAndConteinerForItems();
public slots:
    void AddDayListItem();
    void addImageInList(int index);
    void getTimeEditUpdatetData(int id,QTime startTime,QTime endTime);
    void receiveDayImageListEditSignal(int id);
private slots:
    void on_ButtonAddNewItemOfDayList_clicked();

    void on_TimeTabDayListTabButtonBox_accepted();

    void on_TimeTabDayListTabButtonBox_rejected();




};

#endif // TIMETABDAYLISTWIDGET_H
