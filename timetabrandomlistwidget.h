#ifndef TIMETABRANDOMLISTWIDGET_H
#define TIMETABRANDOMLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagelist.h"
#include "dialogwindowlistofimage.h"
#include "dbrandomlisttablemanager.h"
#include "baselistwidget.h"
namespace Ui {
class TimeTabRandomListWidget;
}

class TimeTabRandomListWidget :  public BaseListWidget
{
    Q_OBJECT

public:
    explicit TimeTabRandomListWidget(QWidget *parent = nullptr);
    ~TimeTabRandomListWidget();

    void CreateInterfaceViewTab();
    void CreatInterfaceCreateTab();
    void CreateViewTabItem();
    void UpdateViewTabItem();
    void PrepareTabForEditingItem(int ListId) override;
    void PrepareTabForCreatingItem() override;

public slots:
    void AcceptSavingOfList() override;
    void addImageInList(int index) override;

    void ShowDialogWindowListOfImage();
private:
    bool ValidateDataViewList();


    Ui::TimeTabRandomListWidget *ui;
    DBRandomListTableManager dbRandomListTableManager;

    QScopedPointer<RandomImageList> CurrentRandomImageList;
    QVector<RandomImageList>  RandomImageLists;
    QVector<int> currentImageIds;

    QTimeEdit* timeEdit;

};

#endif // TIMETABRANDOMLISTWIDGET_H
