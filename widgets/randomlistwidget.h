#ifndef RANDOMLISTWIDGET_H
#define RANDOMLISTWIDGET_H

#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagelist.h"
#include "dialogwindowlistofimage.h"
#include "randomlisttablemanager.h"
#include "timetabchildrenwidget.h"
namespace Ui {
class RandomListWidget;
}

class RandomListWidget :  public TimeTabChildrenWidget
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
    void BuildCreateTabInterface() override;
    void ConnectSignals() override;

    Ui::RandomListWidget *ui;
    RandomListTableManager dbManager;

    QScopedPointer<RandomImageList> CurrentRandomImageList;
    QVector<RandomImageList>  RandomImageLists;
    QVector<int> currentImageIds;

    QTimeEdit* timeEdit;

};

#endif // RANDOMLISTWIDGET_H
