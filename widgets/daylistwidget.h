#ifndef DAYLISTWIDGET_H
#define DAYLISTWIDGET_H

#include <QWidget>
#include "DB/sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "models/imagelist.h"
#include "windowlistofimage.h"
#include "DB/TablesManagers/daylisttablemanager.h"
#include "timetabchildrenwidget.h"
namespace Ui {
class DayListWidget;
}

class DayListWidget : public TimeTabChildrenWidget
{
    Q_OBJECT
private:
    Ui::DayListWidget *ui;
    DayListTableManager dbManager;

    QScopedPointer<DayImageList> currentDayImageList;
    QVector<DayImageList> DayImageLists;
    QVector<TimeRangeImage> currentImageIds;

    bool ValidateDataViewList();
    void BuildCreateTabInterface();
    void ConnectSignals() override;

public:
    explicit DayListWidget(QWidget *parent = nullptr);
    ~DayListWidget();
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

#endif // DAYLISTWIDGET_H
