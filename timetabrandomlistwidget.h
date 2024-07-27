#ifndef TIMETABRANDOMLISTWIDGET_H
#define TIMETABRANDOMLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imageslist.h"
#include "dialogwindowlistofimage.h"
#include "dbrandomlisttablemanager.h"
namespace Ui {
class TimeTabRandomListWidget;
}

class TimeTabRandomListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTabRandomListWidget(DBManager* dbManager, ImagesList *imagesList, DialogWindowListOfImage *dialogWindowListOfImage, QWidget *parent = nullptr);
    ~TimeTabRandomListWidget();
    void setStyleIntoPage();
    void CreateViewTabInterface();
    void CreatInterfaceCreateTab();
    void CreateViewTabItem();
    void UpdateViewTabItem();
     void SetScrollAreaAndConteinerForItems();
private slots:

    void on_ButtonAddNewItemOfRandomList_clicked();



    void on_TimeTabRandomListTabButtonBox_accepted();

    void on_TimeTabRandomListTabButtonBox_rejected();

public slots:
    void addImageInList(int index);
    void AddRandomListItem();
    void receiveRandomImageListEditSignal(int id);

private:
    Ui::TimeTabRandomListWidget *ui;
    DialogWindowListOfImage* dialogWindowListOfImage;
    QWidget *scrollAreaConterinerCreateTab;
    QWidget *scrollAreaConterinerViewTab;

    DBManager* dbManager;
    ImagesList *imagesList;
    InterfaceAddition* interfaceAddition;
    ScrollAreaManager* scrollAreaManager;
    DBRandomListTableManager dbRandomListTableManager;

    RandomImageList*  CurrentRandomImageList;
       QVector<RandomImageList>  RandomImageLists;
    //QScrollArea* scrollArea ;
    QVector<int> currentImageIds;
};

#endif // TIMETABRANDOMLISTWIDGET_H
