#include "randomlistwidget.h"
#include "ui_randomlistwidget.h"

RandomListWidget::RandomListWidget(QWidget* parent)
    : BaseListWidget(parent), ui(new Ui::RandomListWidget)
{
    ui->setupUi(this);
    CurrentRandomImageList.reset(new RandomImageList());
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonAddImageClicked, this, &RandomListWidget::ShowDialogWindowListOfImage);

    tabCreateList = tabInterfaceBuilder->buildTabCreateListForRandomList(tabWidget,scrollAreaConterinerCreateTab);
    tabWidget->addTab(tabCreateList, "Craete List");

    nameLineEdit = tabInterfaceBuilder->CreateLineEdit(tabCreateList,WidgetGeometry(110,30,90,10));
    timeEdit = tabInterfaceBuilder->CreateTimeEdit(tabCreateList,WidgetGeometry(70,30,410,10));
    CreateInterfaceViewTab();
}

RandomListWidget::~RandomListWidget()
{
    delete ui;
}

void RandomListWidget::CreateInterfaceViewTab()
{
    RandomImageLists = dbRandomListTableManager.getAllRandomImageLists();
    for (const auto& list : RandomImageLists)
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildRandomListOfImageView(&list));
}

void RandomListWidget::CreatInterfaceCreateTab()
{
    for (int i = 0; i < currentImageIds.size(); i++){
        QWidget* itemWidget = interfaceAddition->BuildRandomListOfImageItem(imageList->findImageById(currentImageIds[i]));
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, itemWidget);
    }
}

void RandomListWidget::CreateViewTabItem()
{
    CurrentRandomImageList.reset(new RandomImageList(nameLineEdit->text(), timeEdit->dateTime(), currentImageIds));
    dbRandomListTableManager.insertImageList(CurrentRandomImageList.data());
}

void RandomListWidget::UpdateViewTabItem()
{
    CurrentRandomImageList->setName(nameLineEdit->text());
    CurrentRandomImageList->setTimeInterval(timeEdit->dateTime());
    CurrentRandomImageList->setImageIds(currentImageIds);
    dbRandomListTableManager.updateRandomImageList(CurrentRandomImageList.data());
}

void RandomListWidget::PrepareTabForCreatingItem()
{
    CurrentRandomImageList.reset(new RandomImageList());
    nameLineEdit->clear();
    timeEdit->setTime(QTime(0, 0));
    currentImageIds.clear();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    tabWidget->setCurrentIndex(1);
}

void RandomListWidget::PrepareTabForEditingItem(int ListId)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CurrentRandomImageList.reset(new RandomImageList(dbRandomListTableManager.FindRandomImageListById(ListId)));
    currentImageIds = CurrentRandomImageList->getImageIds();
    nameLineEdit->setText(CurrentRandomImageList->getName());
    timeEdit->setTime(CurrentRandomImageList->getTimeInterval().time());
    CreatInterfaceCreateTab();
}

void RandomListWidget::addImageInList(int index)
{
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildRandomListOfImageItem(index));
    currentImageIds.append(imageList->GetImageByIndex(index).getId());
    dialogWindowController->Close();
}

void RandomListWidget::ShowDialogWindowListOfImage()
{
    dialogWindowController->Open(this);
}

bool RandomListWidget::ValidateDataViewList()
{
    if(nameLineEdit->text().isEmpty() ||
            timeEdit->text().isEmpty() ||
           2 > currentImageIds.size()) {
        return false;
    } else {
        return true;
    }
}

void RandomListWidget::AcceptSavingOfList()
{
    if(ValidateDataViewList()){
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
    else{
        QMessageBox::warning(this, "Warning", "Before creating the list, please make sure that you have entered a name, set the time interval, and added at least two images.");
    }
}

