#ifndef TIMETABDAYLISTWIDGET_H
#define TIMETABDAYLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagelist.h"
#include "dialogwindowlistofimage.h"
#include "dbdaylisttablemanager.h"
#include "baselistwidget.h"
namespace Ui {
class TimeTabDayListWidget;
}

class TimeTabDayListWidget : public BaseListWidget
{
    Q_OBJECT
private:
    Ui::TimeTabDayListWidget *ui;
    DBDayListTableManager dbDayListTableManager;

    QScopedPointer<DayImageList> currentDayImageList;
    QVector<DayImageList> DayImageLists;
    QVector<TimeRangeImage> currentImageIds;

     bool ValidateDataViewList();

public:
    explicit TimeTabDayListWidget(QWidget *parent = nullptr);
    ~TimeTabDayListWidget();
    void CreateInterfaceViewTab();
    void CreatInterfaceCreateTab();
    void UpdateViewTabItem();
    void CreateViewTabItem();
    void PrepareTabForEditingItem(int ListId) override;
    void PrepareTabForCreatingItem() override;
public slots:
    void AcceptSavingOfList() override;
    void addImageInList(int index) override;

    void ShowDialogWindowListOfImage();

    void getTimeEditUpdatetData(int id,QTime startTime,QTime endTime);



};

#endif // TIMETABDAYLISTWIDGET_H
