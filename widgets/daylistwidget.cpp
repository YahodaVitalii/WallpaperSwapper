#include "daylistwidget.h"
#include "ui_daylistwidget.h"
DayListWidget::DayListWidget(QWidget *parent)
    : TimeTabChildrenWidget(parent), ui(new Ui::DayListWidget)
{
    ui->setupUi(this);

    currentDayImageList.reset(new DayImageList());

    BuildCreateTabInterface();
    CreateInterfaceViewTab();
    ConnectSignals();
}

void DayListWidget::ConnectSignals()
{
    connect(interfaceAddition, &InterfaceAddition::updateTimeEdit, this, &DayListWidget::getTimeEditUpdatetData);
    connect(uiElementEventHandler, &UIElementEventHandler::ButtonAddImageClicked, this, &DayListWidget::ShowDialogWindowListOfImage);
}

DayListWidget::~DayListWidget()
{
    delete ui;
}

void DayListWidget::CreateInterfaceViewTab()
{
    DayImageLists = dbManager.getAllRecords();
    for (auto& list : DayImageLists) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildDayListView(&list));
    }
}

void DayListWidget::CreatInterfaceCreateTab()
{
    for (auto& item : currentImageIds) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildDayListItem(&item));
    }
}
bool DayListWidget::ValidateDataViewList()
{
    if(nameLineEdit->text().isEmpty() ||
            2 > currentImageIds.size()) {
        return false;
    } else {
        return true;
    }
}
void DayListWidget::UpdateViewTabItem()
{
    currentDayImageList->setName(nameLineEdit->text());
    currentDayImageList->setImages(currentImageIds);
    dbManager.updateList(*currentDayImageList.data());
}

void DayListWidget::CreateViewTabItem()
{
    currentDayImageList.reset(new DayImageList(nameLineEdit->text(), currentImageIds));
    dbManager.insertIntoTable(*currentDayImageList.data());
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildDayListView(currentDayImageList.data()));
}

void DayListWidget::PrepareTabForEditingItem(int ListId)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    currentDayImageList.reset(new DayImageList(dbManager.findListById(ListId)));
    nameLineEdit->setText(currentDayImageList->getName());
    currentImageIds = currentDayImageList->getImages();
    CreatInterfaceCreateTab();
}

void DayListWidget::PrepareTabForCreatingItem()
{
    currentDayImageList.reset(new DayImageList());
    nameLineEdit->clear();
    currentImageIds.clear();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    tabWidget->setCurrentIndex(1);
}

void DayListWidget::addImageInList(int index)
{
    int id;
    if (currentImageIds.isEmpty()) {
        id = 1;
    } else {
        id = currentImageIds.last().id + 1;
    }
    TimeRangeImage newImage("00:00", "00:00", index, id);
    currentImageIds.push_back(newImage);
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildDayListItem(&newImage));

    dialogWindowController->Close();
}

void DayListWidget::getTimeEditUpdatetData(int id, QTime startTime, QTime endTime)
{
    qDebug() <<id;
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

void DayListWidget::ShowDialogWindowListOfImage()
{
    dialogWindowController->Open(DialogWindows::ListOfWidget,this);
}

void DayListWidget::AcceptSavingOfList()
{
    if(ValidateDataViewList()){
        int CurrenDayListId = currentDayImageList->getId();
        try{
            if (CurrenDayListId == -1) {
                CreateViewTabItem();
            } else if (CurrenDayListId > 0) {
                UpdateViewTabItem();
                scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
                CreateInterfaceViewTab();
            }else {
                throw WSException("Error: Day List has incorrect index: " + CurrenDayListId);
            }
        } catch (const WSException& e) {
            qDebug() << e.what();
        }

        tabWidget->setCurrentIndex(0);
    }
    else{
        QMessageBox::warning(this, "Warning", "Before creating the list, please make sure that you have entered a name and added at least two images with setted time.");
    }
}
void DayListWidget::BuildCreateTabInterface()
{
    TimeTabChildrenWidget::BuildCreateTabInterface();
    uiElementFactory->CreateButtonAddImage(tabCreateList,WidgetGeometry(90,30,500,10));
}


