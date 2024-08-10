#include "timetabdaylistwidget.h"
#include "ui_timetabdaylistwidget.h"

TimeTabDayListWidget::TimeTabDayListWidget(ImageList *imageList, QWidget *parent)
    : BaseListWidget(imageList, parent), ui(new Ui::TimeTabDayListWidget)
{
    ui->setupUi(this);
    connect(interfaceAddition, &InterfaceAddition::updateTimeEdit, this, &TimeTabDayListWidget::getTimeEditUpdatetData);
     connect(uiElementEventHandler, &UIElementEventHandler::ButtonAddImageClicked, this, &TimeTabDayListWidget::ShowDialogWindowListOfImage);
    currentDayImageList.reset(new DayImageList());

    tabCreateList = tabInterfaceBuilder->buildTabCreateListForDayList(tabWidget,scrollAreaConterinerCreateTab);
    tabWidget->addTab(tabCreateList, "Craete List");

    nameLineEdit = tabInterfaceBuilder->CreateLineEdit(tabCreateList,WidgetGeometry(110,30,90,10));

    CreateInterfaceViewTab();
}

TimeTabDayListWidget::~TimeTabDayListWidget()
{
    delete ui;
}

void TimeTabDayListWidget::CreateInterfaceViewTab()
{
    DayImageLists = dbDayListTableManager.getAllDayImageLists();
    for (auto& list : DayImageLists) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildDayListOfImageView(&list));
    }
}

void TimeTabDayListWidget::CreatInterfaceCreateTab()
{
    for (auto& item : currentImageIds) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildDayListOfImageItem(&item));
    }
}

void TimeTabDayListWidget::UpdateViewTabItem()
{
    currentDayImageList->setName(nameLineEdit->text());
    currentDayImageList->setImages(currentImageIds);
    dbDayListTableManager.updateDayImageList(currentDayImageList.data());
}

void TimeTabDayListWidget::CreateViewTabItem()
{
    currentDayImageList.reset(new DayImageList(nameLineEdit->text(), currentImageIds));
    dbDayListTableManager.insertDayImageList(currentDayImageList.data());
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildDayListOfImageView(currentDayImageList.data()));
}

void TimeTabDayListWidget::PrepareTabForEditingItem(int ListId)
{
    int id;
    if (currentImageIds.isEmpty()) {
        id = 1;
    } else {
        id = currentImageIds.last().id + 1;
    }
    TimeRangeImage newImage("", "", ListId, id);
    currentImageIds.push_back(newImage);
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildDayListOfImageItem(&newImage));

    dialogWindowController->Close();
}

void TimeTabDayListWidget::PrepareTabForCreatingItem()
{
    currentDayImageList.reset(new DayImageList());
    nameLineEdit->clear();
    currentImageIds.clear();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    tabWidget->setCurrentIndex(1);
}

void TimeTabDayListWidget::CreateViewListItem()
{
    PrepareTabForCreatingItem();
}

void TimeTabDayListWidget::addImageInList(int index)
{
    PrepareTabForEditingItem(index);
}

void TimeTabDayListWidget::getTimeEditUpdatetData(int id, QTime startTime, QTime endTime)
{
    QString startTimeStr = startTime.toString("HH:mm");
    QString endTimeStr = endTime.toString("HH:mm");

    for (auto& image : currentImageIds) {
        if (image.id == id) {
            image.startTime = startTimeStr;
            image.endTime = endTimeStr;
            qDebug() << "Updated image with id:" << id;
            qDebug() << "New startTime:" << image.startTime;
            qDebug() << "New endTime:" << image.endTime;
            return;
        }
    }

    qDebug() << "Image with id:" << id << "not found in currentImageIds.";
}

void TimeTabDayListWidget::ReceiveEditSignalForListView(int id)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    currentDayImageList.reset(new DayImageList(dbDayListTableManager.findDayImageListById(id)));
    nameLineEdit->setText(currentDayImageList->getName());
    currentImageIds = currentDayImageList->getImages();
    CreatInterfaceCreateTab();
}

void TimeTabDayListWidget::ShowDialogWindowListOfImage()
{
    dialogWindowController->Open(this);
}

void TimeTabDayListWidget::AcceptSavingOfList()
{
    int CurrenDayListId = currentDayImageList->getId();
    try{
        if (CurrenDayListId == -1) {
            CreateViewTabItem();
        } else if (CurrenDayListId > 0) {
            UpdateViewTabItem();
            scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
            CreateInterfaceViewTab();
        }else {
            throw WSExeptions("Error: Day List has incorrect index: " + CurrenDayListId);
        }
    } catch (const WSExeptions& e) {
        qDebug() << e.what();
    }

    tabWidget->setCurrentIndex(0);
}

void TimeTabDayListWidget::RejectSavingOfList()
{
    tabWidget->setCurrentIndex(0);
}

