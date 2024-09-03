#ifndef BASELISTWIDGET_H
#define BASELISTWIDGET_H

#include <QObject>
#include <QWidget>
#include "sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "imagelist.h"
#include "dialogwindowlistofimage.h"
#include <QTabWidget>
#include <QMessageBox>
#include "tabinterfacebuilder.h"
#include "dialogwindowcontroller.h"

class BaseListWidget: public QWidget
{
    Q_OBJECT
public:
    explicit BaseListWidget(QWidget* parent = nullptr);
    ~BaseListWidget();
public slots:
    virtual void AcceptSavingOfList() = 0;
    virtual void addImageInList(int index) = 0;
    void ReceiveEditSignalForListView(int id);
    void RejectSavingOfList();
    void  CreateViewListItem();


protected:
    ImageList *imageList;
    InterfaceAddition* interfaceAddition;
    TabInterfaceBuilder* tabInterfaceBuilder;
    UIElementEventHandler *uiElementEventHandler;
    ScrollAreaManager* scrollAreaManager;
    DialogWindowController* dialogWindowController;

    QLineEdit* nameLineEdit;

    QTabWidget* tabWidget;
    QWidget* tabCreateList;
    QWidget* tabViewLists;
    QWidget *scrollAreaConterinerCreateTab;
    QWidget *scrollAreaConterinerViewTab;

    virtual void PrepareTabForCreatingItem() =0;
    virtual void PrepareTabForEditingItem(int ListId) =0;
    virtual bool ValidateDataViewList();
private:
    void ConnectSignals();
};

#endif // BASELISTWIDGET_H
