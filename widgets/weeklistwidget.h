#ifndef WEEKLISTWIDGET_H
#define WEEKLISTWIDGET_H

#include <QWidget>
#include "DB/sqlitedbmanager.h"
#include "models/imagelist.h"
#include "windowlistofimage.h"
#include "models/weekimagelist.h"
#include "DB/TablesManagers/weeklisttablemanager.h"
#include "timetabchildrenwidget.h"
#include "enums/dayofweek.h"
namespace Ui {
class WeekListWidget;
}

class WeekListWidget : public TimeTabChildrenWidget
{
    Q_OBJECT
private:
    bool ValidateDataViewList();
    void ConnectSignals() override;

    Ui::WeekListWidget *ui;
    WeekListTableManager dbManager;

    QVector<WeekImageList>  WeekImageLists;
    QScopedPointer<WeekImageList> currentWeekImageList;
    QMap<DayOfWeek, int> currentImageIds;
    DayOfWeek currentDay;

public:
    explicit WeekListWidget(QWidget *parent = nullptr);
    ~WeekListWidget();
    void CreatInterfaceCreateTab();
    void CreateInterfaceViewTab();
    void CreateViewTabItem();
    void  UpdateViewTabItem();
    void PrepareTabForEditingItem(int ListId) override;
    void PrepareTabForCreatingItem() override;

    QMap<DayOfWeek, int> fillCurrentImageIds();
public slots:
    void AcceptSavingOfList() override;
    void addImageInList(int index) override;

    void ShowDialogWindowListOfImage(int itemId);

};

#endif // WEEKLISTWIDGET_H
