#include "timetabwidgets.h"

TimeTabWidgets::TimeTabWidgets(QWidget* parent)
    : BaseListWidget(parent)
{
    this->move(10,100);
    this->setStyleSheet(Style::getTimeTabStyle());
    tabViewLists = buildTabViewLists(this,scrollAreaConterinerViewTab,WidgetGeometry( 600, 360, 0, 10));

    scrollAreaConterinerCreateTab =  new QWidget(this);

    BuildTabWidget();
    //BuildCreateTabInterface();
    ConnectSignals();
}
TimeTabWidgets::~TimeTabWidgets() {}

void TimeTabWidgets::BuildTabWidget()
{
    tabWidget = uiElementFactory->CreateTabWidget(this);
    tabWidget->show();
    tabWidget->addTab(tabViewLists, "View Lists");
}
void TimeTabWidgets::ConnectSignals()
{
    BaseListWidget::ConnectSignals();
    connect(uiElementEventHandler, &UIElementEventHandler::sendEditSignalToItem, this, &TimeTabWidgets::ReceiveEditSignalForListView);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxAccepted, this, &TimeTabWidgets::AcceptSavingOfList);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxRejected, this, &TimeTabWidgets::RejectSavingOfList);
}
void TimeTabWidgets::ReceiveEditSignalForListView(int id)
{
    PrepareTabForEditingItem(id);
}

void TimeTabWidgets::RejectSavingOfList()
{
    tabWidget->setCurrentIndex(0);
}

void TimeTabWidgets::CreateViewListItem()
{
    PrepareTabForCreatingItem();
}

bool TimeTabWidgets::ValidateDataViewList()
{
    if(nameLineEdit->text().isEmpty()){
        return false;
    }
    else{
        return true;
    }
}

void TimeTabWidgets::BuildCreateTabInterface()
{
    tabCreateList = new QWidget(this);
    tabCreateList->setStyleSheet(Style::getCreateTabStyle());

    scrollAreaManager->initVBoxLayout(scrollAreaConterinerCreateTab);
    scrollAreaManager->CreateScrollArea(tabCreateList, scrollAreaConterinerCreateTab, WidgetGeometry(600, 280, 0, 60));
    tabWidget->addTab(tabCreateList, "Create List");

    uiElementFactory->CreateLableWithText(tabCreateList,"Name:",30,15);
    nameLineEdit = uiElementFactory->CreateLineEdit(tabCreateList, WidgetGeometry(110, 30, 90, 10));
    uiElementFactory->CreateButtonBox(tabCreateList,430,340);
}
