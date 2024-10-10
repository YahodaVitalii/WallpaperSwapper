#ifndef RANDOMLISTWIDGET_H
#define RANDOMLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagelist.h"
#include "dialogwindowlistofimage.h"
#include "dbrandomlisttablemanager.h"
#include "timetabwidgets.h"
namespace Ui {
class RandomListWidget;
}

class RandomListWidget :  public TimeTabWidgets
{
    Q_OBJECT

public:
    explicit RandomListWidget(QWidget *parent = nullptr);
    ~RandomListWidget();

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


    Ui::RandomListWidget *ui;
    DBRandomListTableManager dbManager;

    QScopedPointer<RandomImageList> CurrentRandomImageList;
    QVector<RandomImageList>  RandomImageLists;
    QVector<int> currentImageIds;

    QTimeEdit* timeEdit;

};

#endif // RANDOMLISTWIDGET_H
