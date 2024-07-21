#ifndef TIMETABWEEKLISTWIDGET_H
#define TIMETABWEEKLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include "imageslist.h"
#include "interfaceaddition.h"
#include "dialogwindowlistofimage.h"
#include "weekimagelist.h"
namespace Ui {
class TimeTabWeekListWidget;
}

class TimeTabWeekListWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::TimeTabWeekListWidget *ui;
    DialogWindowListOfImage* dialogWindowListOfImage;
    QWidget *scrollAreaConterinerCreateTab;
    QWidget *scrollAreaConterinerViewTab;

    DBManager* dbManager;
    ImagesList *imagesList;
    InterfaceAddition* interfaceAddition;
    ScrollAreaManager* scrollAreaManager;

     QVector<WeekImageList>  WeekImageLists;
    WeekImageList* currentWeekImageList;
    QMap<QString, int> currentImageIds;
     QStringList days = {"Other days","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

     QString currentDay;

public:
    explicit TimeTabWeekListWidget(DBManager* dbManager, ImagesList *imagesList, QWidget *parent = nullptr);
    ~TimeTabWeekListWidget();
    void SetTimeTabWeekListWidgetStyle();
    void CreateDialogWindowListOfImage();
    void CreateTabCreateListOfWidgets();
    void CreateTabViewListOfWidgets();
    void AddNewWeekImageList();
   void  UpdateViewTabItem();
   void SetScrollAreaAndConteinerForItems();
     QMap<QString, int> fillCurrentImageIds(const QStringList& keys);
private slots:


    void on_CreateTabButtonBox_accepted();

    void on_CreateTabButtonBox_rejected();

public slots:
    void AddWeekListItem();
    void ShowDialogWindow(QString day);
    void addImageInItem(int index);
    void  receiveWeekImageListEditSignal(int id);

};

#endif // TIMETABWEEKLISTWIDGET_H
