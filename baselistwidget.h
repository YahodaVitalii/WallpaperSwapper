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
#include "tabinterfacebuilder.h"
#include "dialogwindowcontroller.h"

class BaseListWidget: public QWidget
{
    Q_OBJECT
public:
    explicit BaseListWidget(ImageList *imageList, QWidget* parent = nullptr);
    ~BaseListWidget();
public slots:
    virtual void ReceiveEditSignalForListView(int id) = 0;
    virtual void AcceptSavingOfList() = 0;
    virtual void RejectSavingOfList() = 0;
    //void  CreateViewListItem();
    virtual void addImageInList(int index) = 0;

protected:
    ImageList *imageList;
   // DialogWindowListOfImage *dialogWindowListOfImage;
    InterfaceAddition* interfaceAddition;
    TabInterfaceBuilder* tabInterfaceBuilder;
     UIElementEventHandler *uiElementEventHandler;
    ScrollAreaManager* scrollAreaManager;
    DialogWindowController* dialogWindowController;

    QTabWidget* tabWidget;
    QLineEdit* nameLineEdit;


    QWidget* tabCreateList;
    QWidget* tabViewLists;
    QWidget *scrollAreaConterinerCreateTab;
    QWidget *scrollAreaConterinerViewTab;
};

#endif // BASELISTWIDGET_H
