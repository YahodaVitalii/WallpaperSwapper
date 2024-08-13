#include "baselistwidget.h"

BaseListWidget::BaseListWidget(ImageList* imageList, QWidget* parent)
    : QWidget(parent), imageList(imageList)
{
    scrollAreaConterinerCreateTab =  new QWidget(this);
    scrollAreaConterinerViewTab =  new QWidget(this);
    uiElementEventHandler = new UIElementEventHandler();
    interfaceAddition = new InterfaceAddition(this,uiElementEventHandler);
    tabInterfaceBuilder = new TabInterfaceBuilder(this,uiElementEventHandler);
    dialogWindowController = new DialogWindowController(uiElementEventHandler);


    tabWidget = tabInterfaceBuilder->CreateTabWidget(this);
    tabWidget->show();

    tabViewLists = tabInterfaceBuilder->buildTabViewLists(tabWidget,scrollAreaConterinerViewTab);
    tabWidget->addTab(tabViewLists, "View Lists");




    connect(uiElementEventHandler, &UIElementEventHandler::sendEditSignalToItem, this, &BaseListWidget::ReceiveEditSignalForListView);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxAccepted, this, &BaseListWidget::AcceptSavingOfList);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxRejected, this, &BaseListWidget::RejectSavingOfList);
    connect(uiElementEventHandler, &UIElementEventHandler::imageSelected, this, &BaseListWidget::addImageInList);

}

BaseListWidget::~BaseListWidget()
{
    delete scrollAreaConterinerCreateTab;
    delete scrollAreaConterinerViewTab;
    delete interfaceAddition;
    delete tabInterfaceBuilder;
    delete tabWidget;
    //delete tabViewLists;
    //delete tabCreateList;
}



