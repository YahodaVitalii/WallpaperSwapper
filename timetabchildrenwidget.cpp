#include "timetabchildrenwidget.h"

TimeTabChildrenWidget::TimeTabChildrenWidget(QWidget* parent)
    : BaseListWidget(parent)
{
    this->move(10,100);
    this->setStyleSheet(Style::getTimeTabStyle());
    tabViewLists = buildTabViewLists(this,scrollAreaConterinerViewTab,WidgetGeometry( 600, 360, 0, 10));

    scrollAreaConterinerCreateTab =  new QWidget(this);

    BuildTabWidget();
    ConnectSignals();
}
TimeTabChildrenWidget::~TimeTabChildrenWidget() {}

void TimeTabChildrenWidget::BuildTabWidget()
{
    tabWidget = uiElementFactory->CreateTabWidget(this);
    tabWidget->show();
    tabWidget->addTab(tabViewLists, "View Lists");
}
void TimeTabChildrenWidget::ConnectSignals()
{
    connect(uiElementEventHandler, &UIElementEventHandler::sendEditSignalToItem, this, &TimeTabChildrenWidget::ReceiveEditSignalForListView);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxAccepted, this, &TimeTabChildrenWidget::AcceptSavingOfList);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonBoxRejected, this, &TimeTabChildrenWidget::RejectSavingOfList);
    connect(uiElementEventHandler, &UIElementEventHandler::sendList, this, &TimeTabChildrenWidget::ResendList);
}
void TimeTabChildrenWidget::ReceiveEditSignalForListView(int id)
{
    PrepareTabForEditingItem(id);
}

void TimeTabChildrenWidget::RejectSavingOfList()
{
    tabWidget->setCurrentIndex(0);
}

void TimeTabChildrenWidget::CreateViewListItem()
{
    PrepareTabForCreatingItem();
}

void TimeTabChildrenWidget::ResendList(BaseImageList *imageList)
{
    emit resendListSignal(imageList);
}

bool TimeTabChildrenWidget::ValidateDataViewList()
{
    if(nameLineEdit->text().isEmpty()){
        return false;
    }
    else{
        return true;
    }
}

void TimeTabChildrenWidget::BuildCreateTabInterface()
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
