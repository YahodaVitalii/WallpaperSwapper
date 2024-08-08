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

class BaseListWidget: public QWidget
{
    Q_OBJECT
public:
    explicit BaseListWidget(ImageList *imageList, DialogWindowListOfImage* dialogWindowListOfImage, QWidget* parent = nullptr);
    ~BaseListWidget();

public slots:
    virtual void ReceiveEditSignalForListView(int id) = 0;
    virtual void AcceptSavingOfList() = 0;
    virtual void RejectSavingOfList() = 0;
    void addImageInList(int index);

protected:
    ImageList *imageList;
    DialogWindowListOfImage *dialogWindowListOfImage;
    InterfaceAddition* interfaceAddition;
    TabInterfaceBuilder* tabInterfaceBuilder;
    UIElementFactory* uiElementFactory;
    ScrollAreaManager* scrollAreaManager;

    QTabWidget* tabWidget;
    QLineEdit* nameLineEdit;


    QWidget* tabCreateList;
    QWidget* tabViewLists;
    QWidget *scrollAreaConterinerCreateTab;
    QWidget *scrollAreaConterinerViewTab;
};

#endif // BASELISTWIDGET_H
