#include "timetabdaylistwidget.h"
#include "ui_timetabdaylistwidget.h"

TimeTabDayListWidget::TimeTabDayListWidget(DBManager *dbManager, ImageManager *imageManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTabDayListWidget),dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);
    interfaceAddition = new InterfaceAddition(this, dbManager, imageManager);
    SetTimeTabDayListWidgetStyle();
    CreateDialogWindowListOfImage();

    SetScrollAreaAndConteinerForItems();

    CreateViewTabInterface();

    currentDayImageList = new DayImageList();

    connect(interfaceAddition, &InterfaceAddition::updateTimeEdit, this,&TimeTabDayListWidget::getTimeEditUpdatetData);
    connect(interfaceAddition, &InterfaceAddition::sendEditSignalToItem, this, &TimeTabDayListWidget::receiveDayImageListEditSignal);
}

TimeTabDayListWidget::~TimeTabDayListWidget()
{
    delete ui;
}

void TimeTabDayListWidget::SetTimeTabDayListWidgetStyle()
{
    ui->TimeTabDayListTabWidget->tabBar()->hide();
    ui->TimeTabDayListTabWidget->setCurrentIndex(0);
    ui->TimeTabDayListTabWidget->setStyleSheet(Style::getTabWidgetStyle());
    ui->CreateTab->setStyleSheet(Style::getCreateTabStyle());
}

void TimeTabDayListWidget::CreateDialogWindowListOfImage()
{
    dialogWindowListOfImage = new DialogWindowListOfImage(this->dbManager,imageManager,interfaceAddition, this);
    connect(interfaceAddition, &InterfaceAddition::imageSelected, this, &TimeTabDayListWidget::addImageInList);
    dialogWindowListOfImage->setStyleSheet(Style::getTabsStyle());
}



void TimeTabDayListWidget::CreateViewTabInterface()
{
    DayImageLists = dbManager->getAllDayImageLists();
    for(auto& list : DayImageLists){
       interfaceAddition->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->CreateDayListOfImage(&list));
    }
}

void TimeTabDayListWidget::CreatInterfaceCreateTab()
{

    for(auto& item : currentImageIds)
        interfaceAddition->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab ,interfaceAddition->CreateDayListOfImageItem(&item));

}

void TimeTabDayListWidget::UpdateViewTabItem()
{
    currentDayImageList->setName(ui->lineEditName->text());
    currentDayImageList->setImages(currentImageIds);
    dbManager->updateDayImageList(currentDayImageList);
}

void TimeTabDayListWidget::AddNewDayList()
{
    currentDayImageList = new DayImageList(ui->lineEditName->text(),currentImageIds);
    dbManager->insertDayImageList(currentDayImageList);
    interfaceAddition->setWidgetIntoScrollArea(scrollAreaConterinerViewTab,interfaceAddition->CreateDayListOfImage(currentDayImageList));
}

void TimeTabDayListWidget::SetScrollAreaAndConteinerForItems()
{
    scrollAreaConterinerCreateTab = new QWidget(this);
    scrollAreaConterinerViewTab = new QWidget(this);
    QVBoxLayout *layoutCreateTab = new QVBoxLayout(scrollAreaConterinerCreateTab);
    scrollAreaConterinerCreateTab->setLayout(layoutCreateTab);
    QVBoxLayout *layoutViewTab = new QVBoxLayout(scrollAreaConterinerViewTab);
    scrollAreaConterinerViewTab->setLayout(layoutViewTab);
    interfaceAddition->CreateScrollArea(ui->CreateTab, scrollAreaConterinerCreateTab,600,280,0,60);
    interfaceAddition->CreateScrollArea(ui->ViewTab, scrollAreaConterinerViewTab, 600, 360, 0, 10);

}

void TimeTabDayListWidget::AddDayListItem()
{
    currentDayImageList = new DayImageList();
    ui->lineEditName->clear();
    currentImageIds.clear();
    interfaceAddition->ClearConteinerWidget(scrollAreaConterinerCreateTab);
    ui->TimeTabDayListTabWidget->setCurrentIndex(1);
}

void TimeTabDayListWidget::addImageInList(int index)
{

    int id;
    if(currentImageIds.isEmpty()){
        id =1;
    }
    else{
        id = currentImageIds.last().id+1;
    }
    TimeRangeImage newImage("", "", index, id);
    currentImageIds.push_back(newImage);
    interfaceAddition->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab ,interfaceAddition->CreateDayListOfImageItem(&newImage));

    dialogWindowListOfImage ->hide();

}

void TimeTabDayListWidget::getTimeEditUpdatetData(int id, QTime startTime, QTime endTime) {


    // Перетворення QTime на QString
    QString startTimeStr = startTime.toString("HH:mm");
    QString endTimeStr = endTime.toString("HH:mm");

    // Пошук елемента у векторі за id
    for (auto& image : currentImageIds) {
        if (image.id == id) {
            // Заміна startTime і endTime
            image.startTime = startTimeStr;
            image.endTime = endTimeStr;
            qDebug() << "Updated image with id:" << id;
            qDebug() << "New startTime:" << image.startTime;
            qDebug() << "New endTime:" << image.endTime;
            return; // Припиняємо пошук після успішного оновлення
        }
    }

    // Якщо елемент не знайдено
    qDebug() << "Image with id:" << id << "not found in currentImageIds.";
}

void TimeTabDayListWidget::receiveDayImageListEditSignal(int id)
{
    ui->TimeTabDayListTabWidget->setCurrentIndex(1);
    interfaceAddition->ClearConteinerWidget(scrollAreaConterinerCreateTab);
    currentDayImageList = new DayImageList(dbManager->findDayImageListById(id));
    ui->lineEditName->setText(currentDayImageList->getName());
    currentImageIds = currentDayImageList->getImages();
    CreatInterfaceCreateTab();
}

void TimeTabDayListWidget::on_ButtonAddNewItemOfDayList_clicked()
{
    dialogWindowListOfImage->show();
}


void TimeTabDayListWidget::on_TimeTabDayListTabButtonBox_accepted()
{
    ui->TimeTabDayListTabWidget->setCurrentIndex(0);
    if (currentDayImageList->getId() == -1){
        AddNewDayList();
    } else if (currentDayImageList->getId() > 0)
    {
        UpdateViewTabItem();
        interfaceAddition->ClearConteinerWidget(scrollAreaConterinerViewTab);
        CreateViewTabInterface();

    };

}


void TimeTabDayListWidget::on_TimeTabDayListTabButtonBox_rejected()
{
    ui->TimeTabDayListTabWidget->setCurrentIndex(0);
}

