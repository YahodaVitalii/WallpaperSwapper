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
#include <QScopedPointer>
#include "tabinterfacebuilder.h"
#include "dialogwindowcontroller.h"

class BaseListWidget: public QWidget
{
    Q_OBJECT
public:
    explicit BaseListWidget(QWidget* parent = nullptr);
    ~BaseListWidget();
public slots:
    virtual void addImageInList(int index) = 0;
protected:
    ImageList *imageList;
    InterfaceAddition* interfaceAddition;
    TabInterfaceBuilder* tabInterfaceBuilder;
    UIElementEventHandler *uiElementEventHandler;
    ScrollAreaManager* scrollAreaManager;
    DialogWindowController* dialogWindowController;


    QWidget* tabViewLists;
    QWidget *scrollAreaConterinerViewTab;


   virtual void ConnectSignals();
};

#endif // BASELISTWIDGET_H
