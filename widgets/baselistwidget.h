#ifndef BASELISTWIDGET_H
#define BASELISTWIDGET_H

#include <QObject>
#include <QWidget>
#include "DB/sqlitedbmanager.h"
#include <QWidget>
#include <QDebug>
#include "models/imagelist.h"
#include "windowlistofimage.h"
#include <QTabWidget>
#include <QMessageBox>
#include <QScopedPointer>
#include "GUI/service/dialogwindowcontroller.h"
#include "enums/dialogwindows.h"

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
    UIElementEventHandler *uiElementEventHandler;
    UIElementFactory* uiElementFactory;
    ScrollAreaManager* scrollAreaManager;
    DialogWindowController* dialogWindowController;

    QWidget* tabViewLists;
    QWidget *scrollAreaConterinerViewTab;


   virtual void ConnectSignals();
   virtual QWidget* buildTabViewLists(QWidget *conteinerWidget,QWidget *scrollAreaConterinerViewTab,const WidgetGeometry &geometry);
};

#endif // BASELISTWIDGET_H
