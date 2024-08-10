#include "tabinterfacebuilder.h"

TabInterfaceBuilder::TabInterfaceBuilder(QWidget *parent, UIElementEventHandler *uiElementEventHandler): QWidget(parent),uiElementEventHandler(uiElementEventHandler)
{
    uiElementFactory = new UIElementFactory(uiElementEventHandler);
}
QTabWidget *TabInterfaceBuilder::CreateTabWidget(QWidget *conteinerWidget)
{
    QTabWidget* tabWidget = new QTabWidget(conteinerWidget);

    tabWidget->setFixedSize (600, 380);
    tabWidget->tabBar()->hide();
    tabWidget->setStyleSheet(Style::getTabWidgetStyle());

    return tabWidget;

}
QWidget* TabInterfaceBuilder::buildTabCreateListForRandomList(QWidget *conteinerWidget,QWidget *scrollAreaConterinerCreateTab)
{
    QWidget* tabCreateList = new QWidget(conteinerWidget);
    tabCreateList->setStyleSheet(Style::getCreateTabStyle());

    QVBoxLayout *layoutCreateTab = new QVBoxLayout(scrollAreaConterinerCreateTab);
    scrollAreaConterinerCreateTab->setLayout(layoutCreateTab);
    scrollAreaManager.CreateScrollArea(tabCreateList, scrollAreaConterinerCreateTab, 600, 280, 0, 60);


    uiElementFactory->CreateButtonAddImage(tabCreateList,WidgetGeometry(90,30,500,10));
    uiElementFactory->CreateLableWithText(tabCreateList,"Name:",30,15);
    uiElementFactory->CreateLableWithText(tabCreateList,"Change wlapper interval:",220,15);
    uiElementFactory->CreateButtonBox(tabCreateList,430,340);

    return tabCreateList;
}

QWidget *TabInterfaceBuilder::buildTabCreateListForWeekList(QWidget *conteinerWidget, QWidget *scrollAreaConterinerCreateTab)
{
    QWidget* tabCreateList = new QWidget(conteinerWidget);
    tabCreateList->setStyleSheet(Style::getCreateTabStyle());

    QVBoxLayout *layoutCreateTab = new QVBoxLayout(scrollAreaConterinerCreateTab);
    scrollAreaConterinerCreateTab->setLayout(layoutCreateTab);
    scrollAreaManager.CreateScrollArea(tabCreateList, scrollAreaConterinerCreateTab, 600, 280, 0, 60);

    uiElementFactory->CreateLableWithText(tabCreateList,"Name:",30,15);
    uiElementFactory->CreateButtonBox(tabCreateList,430,340);

    return tabCreateList;
}
QWidget *TabInterfaceBuilder::buildTabCreateListForDayList(QWidget *conteinerWidget, QWidget *scrollAreaConterinerCreateTab)
{
    QWidget* tabCreateList = new QWidget(conteinerWidget);
    tabCreateList->setStyleSheet(Style::getCreateTabStyle());

    QVBoxLayout *layoutCreateTab = new QVBoxLayout(scrollAreaConterinerCreateTab);
    scrollAreaConterinerCreateTab->setLayout(layoutCreateTab);
    scrollAreaManager.CreateScrollArea(tabCreateList, scrollAreaConterinerCreateTab, 600, 280, 0, 60);

    uiElementFactory->CreateButtonAddImage(tabCreateList,WidgetGeometry(90,30,500,10));
    uiElementFactory->CreateLableWithText(tabCreateList,"Name:",30,15);
    uiElementFactory->CreateButtonBox(tabCreateList,430,340);

    return tabCreateList;
}

// Function to build the "View Lists" tab
QWidget* TabInterfaceBuilder::buildTabViewLists(QWidget *conteinerWidget,QWidget *scrollAreaConterinerViewTab)
{
    QWidget* tabViewLists = new QWidget(conteinerWidget);

    QVBoxLayout *layoutViewTab = new QVBoxLayout(scrollAreaConterinerViewTab);
    scrollAreaConterinerViewTab->setLayout(layoutViewTab);
    scrollAreaManager.CreateScrollArea(tabViewLists, scrollAreaConterinerViewTab, 600, 360, 0, 10);

    return tabViewLists;
}

QTimeEdit *TabInterfaceBuilder::CreateTimeEdit(QWidget *containerWidget, const WidgetGeometry &geometry)
{
    QTimeEdit* timeEdit = new QTimeEdit(containerWidget);
    timeEdit->setFixedSize(geometry.width, geometry.height);
    timeEdit->move(geometry.xPos, geometry.yPos);
    timeEdit->show();
    return timeEdit;
}
QLineEdit* TabInterfaceBuilder::CreateLineEdit(QWidget *containerWidget, const WidgetGeometry &geometry)
{
    QLineEdit* lineEdit = new QLineEdit(containerWidget);
    lineEdit->setFixedSize(geometry.width, geometry.height);
    lineEdit->move(geometry.xPos, geometry.yPos);
    lineEdit->show();
    return lineEdit;
}
