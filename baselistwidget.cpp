#include "baselistwidget.h"

BaseListWidget::BaseListWidget( QWidget* parent)
    : QWidget(parent)
{
    imageList = SQLTableImageList::getInstance();
    scrollAreaConterinerViewTab =  new QWidget(this);
    uiElementEventHandler = new UIElementEventHandler();
    uiElementFactory = new UIElementFactory(uiElementEventHandler);
    interfaceAddition = new InterfaceAddition(this,uiElementEventHandler);
    dialogWindowController = new DialogWindowController(uiElementEventHandler);



}

BaseListWidget::~BaseListWidget()
{
    delete scrollAreaConterinerViewTab;
    delete interfaceAddition;
}



void BaseListWidget::ConnectSignals()
{
    connect(uiElementEventHandler, &UIElementEventHandler::imageSelected, this, &BaseListWidget::addImageInList);
}
QWidget* BaseListWidget::buildTabViewLists(QWidget *conteinerWidget,QWidget *scrollAreaConterinerViewTab,const WidgetGeometry &geometry)
{
    QWidget* tabViewLists = new QWidget(conteinerWidget);
    tabViewLists->move(geometry.xPos,geometry.yPos);
    scrollAreaManager->initVBoxLayout(scrollAreaConterinerViewTab);
    scrollAreaManager->CreateScrollArea(tabViewLists, scrollAreaConterinerViewTab, geometry);


    return tabViewLists;
}


