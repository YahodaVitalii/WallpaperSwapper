#include "baselistwidget.h"

BaseListWidget::BaseListWidget( QWidget* parent)
    : QWidget(parent)
{
    this->move(10,100);
    this->setStyleSheet(Style::getTimeTabStyle());

    imageList = SQLTableImageList::getInstance();

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

    ConnectSignals();
}

BaseListWidget::~BaseListWidget()
{
    delete scrollAreaConterinerCreateTab;
    delete scrollAreaConterinerViewTab;
    delete interfaceAddition;
    delete tabInterfaceBuilder;
    delete tabWidget;
}

void BaseListWidget::ReceiveEditSignalForListView(int id)
{
PrepareTabForEditingItem(id);
}

void BaseListWidget::RejectSavingOfList()
{
   tabWidget->setCurrentIndex(0);
}

void BaseListWidget::CreateViewListItem()
{
    PrepareTabForCreatingItem();
}

bool BaseListWidget::ValidateDataViewList()
{
    if(nameLineEdit->text().isEmpty()){
   return false;
    }
    else{
         return true;
    }
}

void BaseListWidget::ConnectSignals()
{
    connect(uiElementEventHandler, &UIElementEventHandler::sendEditSignalToItem, this, &BaseListWidget::ReceiveEditSignalForListView);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxAccepted, this, &BaseListWidget::AcceptSavingOfList);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxRejected, this, &BaseListWidget::RejectSavingOfList);
    connect(uiElementEventHandler, &UIElementEventHandler::imageSelected, this, &BaseListWidget::addImageInList);
}



