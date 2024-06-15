#ifndef TIMETABDAYLISTWIDGET_H
#define TIMETABDAYLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagemanager.h"
#include "dialogwindowlistofimage.h"

namespace Ui {
class TimeTabDayListWidget;
}

class TimeTabDayListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTabDayListWidget(DBManager* dbManager, ImageManager *imageManager, QWidget *parent = nullptr);
    ~TimeTabDayListWidget();

    void SetTimeTabDayListWidgetStyle();
    void CreateDialogWindowListOfImage();
public slots:
    void AddDayListItem();
    void addImageInList(int index);
private slots:
    void on_ButtonAddNewItemOfDayList_clicked();

    void on_TimeTabDayListTabButtonBox_accepted();

    void on_TimeTabDayListTabButtonBox_rejected();

private:
    Ui::TimeTabDayListWidget *ui;
    DialogWindowListOfImage* dialogWindowListOfImage;

    DBManager* dbManager;
    ImageManager *imageManager;
    InterfaceAddition* interfaceAddition;

    DayImageList* dayImageList;
    QVector<DayImageList> DayImageLists;
    QVector<TimeRangeImage> currentImageIds;
};

#endif // TIMETABDAYLISTWIDGET_H
