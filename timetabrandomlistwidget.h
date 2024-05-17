#ifndef TIMETABRANDOMLISTWIDGET_H
#define TIMETABRANDOMLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagemanager.h"
#include "dialogwindowlistofimage.h"
namespace Ui {
class TimeTabRandomListWidget;
}

class TimeTabRandomListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTabRandomListWidget(DBManager* dbManager, ImageManager *imageManager, QWidget *parent = nullptr);
    ~TimeTabRandomListWidget();
    void setStyleIntoPage();
    void CreateDialogWindowListOfImage();
    void CreateViewTabInterface();
    void CreatInterfaceCreateTab();
    void CreateViewTabItem();
    void UpdateViewTabItem();
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

    DBManager* dbManager;
    ImageManager *imageManager;
    InterfaceAddition* interfaceAddition;

    RandomImageList*  CurrentRandomImageList;
       QVector<RandomImageList>  RandomImageLists;
    //QScrollArea* scrollArea ;
    QVector<int> currentImageIds;
};

#endif // TIMETABRANDOMLISTWIDGET_H
