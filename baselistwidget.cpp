#include "baselistwidget.h"

BaseListWidget::BaseListWidget(ImageList* imageList, DialogWindowListOfImage* dialogWindowListOfImage, QWidget* parent)
    : QWidget(parent), imageList(imageList), dialogWindowListOfImage(dialogWindowListOfImage)
{
    scrollAreaConterinerCreateTab =  new QWidget(this);
    scrollAreaConterinerViewTab =  new QWidget(this);
    uiElementFactory = new UIElementFactory(imageList);
    interfaceAddition = new InterfaceAddition(this,uiElementFactory);
    tabInterfaceBuilder = new TabInterfaceBuilder(this,uiElementFactory);
    tabWidget = tabInterfaceBuilder->CreateTabWidget(this);
    tabWidget->show();

    tabViewLists = tabInterfaceBuilder->buildTabViewLists(tabWidget,scrollAreaConterinerViewTab);
    tabWidget->addTab(tabViewLists, "View Lists");


    tabWidget->setCurrentIndex(0);

    connect(uiElementFactory, &UIElementFactory::sendEditSignalToItem, this, &BaseListWidget::ReceiveEditSignalForListView);
    connect(uiElementFactory, &UIElementFactory::ButtonBoxAccepted, this, &BaseListWidget::AcceptSavingOfList);
    connect(uiElementFactory, &UIElementFactory::ButtonBoxRejected, this, &BaseListWidget::RejectSavingOfList);
    connect(uiElementFactory, &UIElementFactory::imageSelected, this, &BaseListWidget::addImageInList);

}

BaseListWidget::~BaseListWidget()
{
    delete scrollAreaConterinerCreateTab;
    delete scrollAreaConterinerViewTab;
    delete uiElementFactory;
    delete interfaceAddition;
    delete tabInterfaceBuilder;
    delete tabWidget;
    delete tabViewLists;
    delete tabCreateList;
}

void BaseListWidget::addImageInList(int index)
{
    qDebug()<<index;
}
