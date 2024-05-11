#ifndef TIMETABRRANDOMLISTWIDGET_H
#define TIMETABRRANDOMLISTWIDGET_H
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagemanager.h"
#include "dialogwindowlistofimage.h"
namespace Ui {
class TimeTabrRandomListWidget;
}

class TimeTabrRandomListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTabrRandomListWidget(DBManager* dbManager, ImageManager *imageManager, QWidget *parent = nullptr);
    ~TimeTabrRandomListWidget();
    void CreateDialogWindowListOfImage();
    void ShowDialogWindowListOfImage();
private slots:
    void on_ButtonAddNewItemOfRandomList_clicked();
    void on_TimeTabrRandomListTabButtonBox_accepted();

    void on_TimeTabrRandomListTabButtonBox_rejected();

public slots:
    void addImageInList(int index);
    void AddRandomListItem();
private:
    Ui::TimeTabrRandomListWidget *ui;
    DialogWindowListOfImage* dialogWindowListOfImage;

    DBManager* dbManager;
    ImageManager *imageManager;
    InterfaceAddition* interfaceAddition;


    //QScrollArea* scrollArea ;
    QVector<int> currentImageIds;
};

#endif // TIMETABRRANDOMLISTWIDGET_H
