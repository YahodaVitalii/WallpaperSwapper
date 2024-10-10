#include "timetabwidgets.h"

TimeTabWidgets::TimeTabWidgets(QWidget* parent)
    : BaseListWidget(parent)
{
    this->move(10,100);
    this->setStyleSheet(Style::getTimeTabStyle());
    tabViewLists = tabInterfaceBuilder->buildTabViewLists(this,scrollAreaConterinerViewTab,WidgetGeometry( 600, 360, 0, 10));

    scrollAreaConterinerCreateTab =  new QWidget(this);

    tabWidget = tabInterfaceBuilder->CreateTabWidget(this);
    tabWidget->show();
    tabWidget->addTab(tabViewLists, "View Lists");
    ConnectSignals();
}
TimeTabWidgets::~TimeTabWidgets()
{

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
