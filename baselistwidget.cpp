#include "baselistwidget.h"

BaseListWidget::BaseListWidget( QWidget* parent)
    : QWidget(parent)
{
    imageList = SQLTableImageList::getInstance();
    scrollAreaConterinerViewTab =  new QWidget(this);
    uiElementEventHandler = new UIElementEventHandler();
    interfaceAddition = new InterfaceAddition(this,uiElementEventHandler);
    tabInterfaceBuilder = new TabInterfaceBuilder(this,uiElementEventHandler);
    dialogWindowController = new DialogWindowController(uiElementEventHandler);



}

BaseListWidget::~BaseListWidget()
{
    delete scrollAreaConterinerViewTab;
    delete interfaceAddition;
    delete tabInterfaceBuilder;
}



void BaseListWidget::ConnectSignals()
{
    connect(uiElementEventHandler, &UIElementEventHandler::imageSelected, this, &BaseListWidget::addImageInList);
}



