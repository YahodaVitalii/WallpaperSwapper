#ifndef TIMETABWEEKLISTWIDGET_H
#define TIMETABWEEKLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include "imagelist.h"
#include "dialogwindowlistofimage.h"
#include "weekimagelist.h"
#include "dbweeklisttablemanager.h"
#include "baselistwidget.h"
#include <QScopedPointer>
namespace Ui {
class TimeTabWeekListWidget;
}

class TimeTabWeekListWidget : public BaseListWidget
{
    Q_OBJECT
private:
    Ui::TimeTabWeekListWidget *ui;
    DBWeekListTableManager dbWeekListTableManager;

    const QStringList days = {"Other days","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    QVector<WeekImageList>  WeekImageLists;
    QScopedPointer<WeekImageList> currentWeekImageList;
    QMap<QString, int> currentImageIds;
    QString currentDay;

public:
    explicit TimeTabWeekListWidget(ImageList *imageList, QWidget *parent = nullptr);
    ~TimeTabWeekListWidget();
    void CreatInterfaceCreateTab();
    void CreateInterfaceViewTab();
    void CreateViewTabItem();
    void  UpdateViewTabItem();
    void PrepareTabForEditingItem(int ListId);
    void PrepareTabForCreatingItem();

    QMap<QString, int> fillCurrentImageIds(const QStringList& keys);
public slots:
    void  ReceiveEditSignalForListView(int id) override;
    void AcceptSavingOfList() override;
    void RejectSavingOfList() override;
    void addImageInList(int index) override;

    void ShowDialogWindowListOfImage(QString day);
    void CreateViewListItem();



};

#endif // TIMETABWEEKLISTWIDGET_H
