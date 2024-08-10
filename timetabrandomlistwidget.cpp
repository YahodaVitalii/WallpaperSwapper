#include "timetabrandomlistwidget.h"
#include "ui_timetabrandomlistwidget.h"

TimeTabRandomListWidget::TimeTabRandomListWidget(ImageList *imageList, QWidget* parent)
    : BaseListWidget(imageList, parent), ui(new Ui::TimeTabRandomListWidget)
{
    ui->setupUi(this);
    CurrentRandomImageList.reset(new RandomImageList());
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonAddImageClicked, this, &TimeTabRandomListWidget::ShowDialogWindowListOfImage);

    tabCreateList = tabInterfaceBuilder->buildTabCreateListForRandomList(tabWidget,scrollAreaConterinerCreateTab);
    tabWidget->addTab(tabCreateList, "Craete List");

    nameLineEdit = tabInterfaceBuilder->CreateLineEdit(tabCreateList,WidgetGeometry(110,30,90,10));
    timeEdit = tabInterfaceBuilder->CreateTimeEdit(tabCreateList,WidgetGeometry(70,30,410,10));
    CreateInterfaceViewTab();
}

TimeTabRandomListWidget::~TimeTabRandomListWidget()
{
    delete ui;
}

void TimeTabRandomListWidget::CreateInterfaceViewTab()
{
    RandomImageLists = dbRandomListTableManager.getAllRandomImageLists();
    for (const auto& list : RandomImageLists)
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildRandomListOfImageView(&list));
}

void TimeTabRandomListWidget::CreatInterfaceCreateTab()
{
    for (int i = 0; i < currentImageIds.size(); i++){
        QWidget* itemWidget = interfaceAddition->BuildRandomListOfImageItem(imageList->findImageById(currentImageIds[i]));
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, itemWidget);
    }
}

void TimeTabRandomListWidget::CreateViewTabItem()
{
    CurrentRandomImageList.reset(new RandomImageList(nameLineEdit->text(), timeEdit->dateTime(), currentImageIds));
    dbRandomListTableManager.insertImageList(CurrentRandomImageList.data());
}

void TimeTabRandomListWidget::UpdateViewTabItem()
{
    CurrentRandomImageList->setName(nameLineEdit->text());
    CurrentRandomImageList->setTimeInterval(timeEdit->dateTime());
    CurrentRandomImageList->setImageIds(currentImageIds);
    dbRandomListTableManager.updateRandomImageList(CurrentRandomImageList.data());
}

void TimeTabRandomListWidget::PrepareTabForCreatingItem()
{
    CurrentRandomImageList.reset(new RandomImageList());
    timeEdit->setTime(QTime(0, 0));
    currentImageIds.clear();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    tabWidget->setCurrentIndex(1);
}

void TimeTabRandomListWidget::PrepareTabForEditingItem(int ListId)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CurrentRandomImageList.reset(new RandomImageList(dbRandomListTableManager.FindRandomImageListById(ListId)));
    currentImageIds = CurrentRandomImageList->getImageIds();
    nameLineEdit->setText(CurrentRandomImageList->getName());
    timeEdit->setTime(CurrentRandomImageList->getTimeInterval().time());
    CreatInterfaceCreateTab();
}

void TimeTabRandomListWidget::addImageInList(int index)
{
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildRandomListOfImageItem(index));
    currentImageIds.append(imageList->GetImageByIndex(index).getId());
    dialogWindowController->Close();
}

void TimeTabRandomListWidget::CreateViewListItem()
{
   PrepareTabForCreatingItem();
}

void TimeTabRandomListWidget::ReceiveEditSignalForListView(int id)
{
    PrepareTabForEditingItem(id);
}

void TimeTabRandomListWidget::ShowDialogWindowListOfImage()
{
    dialogWindowController->Open(this);
}

void TimeTabRandomListWidget::AcceptSavingOfList()
{
    try {
        int CurrentRandomListId = CurrentRandomImageList->getId();
        if (CurrentRandomListId == -1) {
            CreateViewTabItem();
            RandomImageLists = dbRandomListTableManager.getAllRandomImageLists();
            scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildRandomListOfImageView(&RandomImageLists.last()));
        } else if (CurrentRandomListId > 0) {
            UpdateViewTabItem();
            scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
            CreateInterfaceViewTab();
        } else {
            throw WSExeptions("Error: Random List has incorrect index: " + CurrentRandomListId);
        }
    } catch (const WSExeptions& e) {
        qDebug() << "Caught WSExeptions: " << e.what();
    }

    tabWidget->setCurrentIndex(0);
}

void TimeTabRandomListWidget::RejectSavingOfList()
{
    tabWidget->setCurrentIndex(0);
}
