#include "timetabrandomlistwidget.h"
#include "ui_timetabrandomlistwidget.h"

TimeTabRandomListWidget::TimeTabRandomListWidget(DBManager* dbManager, ImagesList *imagesList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTabRandomListWidget),dbManager(dbManager),imagesList(imagesList)
{
    ui->setupUi(this);
    interfaceAddition = new InterfaceAddition(this,imagesList);
    scrollAreaManager = new ScrollAreaManager();

    CurrentRandomImageList = new RandomImageList();
    setStyleIntoPage();
    CreateDialogWindowListOfImage();
    SetScrollAreaAndConteinerForItems();
    CreateViewTabInterface();

    connect(interfaceAddition, &InterfaceAddition::sendEditSignalToItem, this, &TimeTabRandomListWidget::receiveRandomImageListEditSignal);

}

TimeTabRandomListWidget::~TimeTabRandomListWidget()
{
    delete ui;
}

void TimeTabRandomListWidget::setStyleIntoPage()
{
    ui->TimeTabRandomListTabWidget->tabBar()->hide();
    ui->TimeTabRandomListTabWidget->setCurrentIndex(0);
    ui->TimeTabRandomListTabWidget->setStyleSheet(Style::getTabWidgetStyle());
    ui->CreateTab->setStyleSheet(Style::getCreateTabStyle());
}

void TimeTabRandomListWidget::CreateDialogWindowListOfImage()
{
    dialogWindowListOfImage = new DialogWindowListOfImage(this->dbManager,imagesList,interfaceAddition, this);
    connect(interfaceAddition, &InterfaceAddition::imageSelected, this, &TimeTabRandomListWidget::addImageInList);
    dialogWindowListOfImage->setStyleSheet(Style::getTabsStyle());
}

void TimeTabRandomListWidget::CreateViewTabInterface()
{
    RandomImageLists = dbManager->getAllRandomImageLists();
    for (const auto& list : RandomImageLists)
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab,interfaceAddition->CreateRandomListOfImageView(&list));
}

void TimeTabRandomListWidget::CreatInterfaceCreateTab()
{
    for (int i = 0; i < currentImageIds.size(); i++){
      QWidget* itemWidget = interfaceAddition->CreateRandomListOfImageItem(imagesList->findImageById(currentImageIds[i]));
      scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab,itemWidget);
    }
}

void TimeTabRandomListWidget::CreateViewTabItem()
{
    CurrentRandomImageList = new RandomImageList(ui->lineEditNameRandoList->text(), ui->timeEditTimeInterval->dateTime(), currentImageIds);
    dbManager->insertImageList(CurrentRandomImageList);
}

void TimeTabRandomListWidget::UpdateViewTabItem()
{
    CurrentRandomImageList->setName(ui->lineEditNameRandoList->text());
    CurrentRandomImageList->setTimeInterval(ui->timeEditTimeInterval->dateTime());
    CurrentRandomImageList->setImageIds(currentImageIds);
    dbManager->updateRandomImageList(CurrentRandomImageList);
}

void TimeTabRandomListWidget::SetScrollAreaAndConteinerForItems()
{
    scrollAreaConterinerCreateTab = new QWidget(this);
    scrollAreaConterinerViewTab = new QWidget(this);
    QVBoxLayout *layoutCreateTab = new QVBoxLayout(scrollAreaConterinerCreateTab);
    scrollAreaConterinerCreateTab->setLayout(layoutCreateTab);
    QVBoxLayout *layoutViewTab = new QVBoxLayout(scrollAreaConterinerViewTab);
    scrollAreaConterinerViewTab->setLayout(layoutViewTab);
    scrollAreaManager->CreateScrollArea(ui->CreateTab, scrollAreaConterinerCreateTab,600,280,0,60);
    scrollAreaManager->CreateScrollArea(ui->ViewTab,scrollAreaConterinerViewTab,600,360,0,10);
}

void TimeTabRandomListWidget::addImageInList(int index)
{
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab,interfaceAddition->CreateRandomListOfImageItem(index));
    currentImageIds.append(imagesList->GetImageByIndex(index).getId());
    dialogWindowListOfImage ->hide();
}

void TimeTabRandomListWidget::AddRandomListItem()
{
    CurrentRandomImageList = new RandomImageList();
    ui->timeEditTimeInterval->setTime(QTime(0, 0));
    currentImageIds.clear();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    ui->TimeTabRandomListTabWidget->setCurrentIndex(1);
}

void TimeTabRandomListWidget::receiveRandomImageListEditSignal(int id)
{
    ui->TimeTabRandomListTabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CurrentRandomImageList = new RandomImageList(dbManager->FindRandomImageListById(id));
    currentImageIds = CurrentRandomImageList->getImageIds();
    qDebug() << currentImageIds.size();
    ui->lineEditNameRandoList->setText(CurrentRandomImageList->getName());
    ui->timeEditTimeInterval->setTime(CurrentRandomImageList->getTimeInterval().time());
    CreatInterfaceCreateTab();
}

void TimeTabRandomListWidget::on_ButtonAddNewItemOfRandomList_clicked()
{
    dialogWindowListOfImage->showDialogWindow();
}

void TimeTabRandomListWidget::on_TimeTabRandomListTabButtonBox_accepted()
{
    ui->TimeTabRandomListTabWidget->setCurrentIndex(0);
    if (CurrentRandomImageList->getId() == -1)
    {
        CreateViewTabItem();
        RandomImageLists = dbManager->getAllRandomImageLists();
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab ,interfaceAddition->CreateRandomListOfImageView(&RandomImageLists.last()));
    }
    else if (CurrentRandomImageList->getId() > 0)
    {
        UpdateViewTabItem();
        scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
        CreateViewTabInterface();

    }
}


void TimeTabRandomListWidget::on_TimeTabRandomListTabButtonBox_rejected()
{
    ui->TimeTabRandomListTabWidget->setCurrentIndex(0);
}

