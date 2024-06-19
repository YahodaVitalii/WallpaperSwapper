#include "timetabrandomlistwidget.h"
#include "ui_timetabrandomlistwidget.h"

TimeTabRandomListWidget::TimeTabRandomListWidget(DBManager* dbManager, ImageManager *imageManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTabRandomListWidget),dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);
    interfaceAddition = new InterfaceAddition(this, dbManager, imageManager);
    CurrentRandomImageList = new RandomImageList();
    setStyleIntoPage();
    CreateDialogWindowListOfImage();
    CreateViewTabInterface();

    interfaceAddition->CreateScrollArea(ui->CreateTab, interfaceAddition->getContainerWidgetRandomImageListCreate(),600,280,0,60);
    interfaceAddition->CreateScrollArea(ui->ViewTab, interfaceAddition->getcontainerWidgetRandomImageListShow(), 600, 360, 0, 10);
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
    dialogWindowListOfImage = new DialogWindowListOfImage(this->dbManager,imageManager,interfaceAddition, this);
    connect(interfaceAddition, &InterfaceAddition::imageSelected, this, &TimeTabRandomListWidget::addImageInList);
    dialogWindowListOfImage->setStyleSheet(Style::getTabsStyle());
}

void TimeTabRandomListWidget::CreateViewTabInterface()
{
    RandomImageLists = dbManager->getAllRandomImageLists();
    for (int i = 0; i < RandomImageLists.size(); i++)
    {
        interfaceAddition->CreateRandomListOfImageView(imageManager->findImageById(RandomImageLists[i].imageIds[0]), RandomImageLists[i].getId(),RandomImageLists[i].getName(),RandomImageLists[i].getTimeInterval().toString());
    }
}

void TimeTabRandomListWidget::CreatInterfaceCreateTab()
{
    for (int i = 0; i < currentImageIds.size(); i++)
    {
        interfaceAddition->CreateRandomListOfImageItem(imageManager->findImageById(currentImageIds[i]));
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

void TimeTabRandomListWidget::addImageInList(int index)
{
    interfaceAddition->CreateRandomListOfImageItem(index);
    currentImageIds.append(imageManager->GetImageByIndex(index).getId());
    dialogWindowListOfImage ->hide();
}

void TimeTabRandomListWidget::AddRandomListItem()
{
    CurrentRandomImageList = new RandomImageList();
    ui->timeEditTimeInterval->setTime(QTime(0, 0));
    currentImageIds.clear();
    interfaceAddition->ClearConteinerWidget(interfaceAddition->getContainerWidgetRandomImageListCreate());
    ui->TimeTabRandomListTabWidget->setCurrentIndex(1);
}

void TimeTabRandomListWidget::receiveRandomImageListEditSignal(int id)
{
    ui->TimeTabRandomListTabWidget->setCurrentIndex(1);
    interfaceAddition->ClearConteinerWidget(interfaceAddition->getContainerWidgetRandomImageListCreate());
    CurrentRandomImageList = new RandomImageList(dbManager->FindRandomImageListById(id));
    currentImageIds = CurrentRandomImageList->getImageIds();
    qDebug() << currentImageIds.size();
    ui->lineEditNameRandoList->setText(CurrentRandomImageList->getName());
    ui->timeEditTimeInterval->setTime(CurrentRandomImageList->getTimeInterval().time());
    CreatInterfaceCreateTab();
}

void TimeTabRandomListWidget::on_ButtonAddNewItemOfRandomList_clicked()
{
    dialogWindowListOfImage->show();
}

void TimeTabRandomListWidget::on_TimeTabRandomListTabButtonBox_accepted()
{
    ui->TimeTabRandomListTabWidget->setCurrentIndex(0);
    if (CurrentRandomImageList->getId() == -1)
    {
        CreateViewTabItem();
        RandomImageLists = dbManager->getAllRandomImageLists();
        interfaceAddition->CreateRandomListOfImageView(imageManager->findImageById(RandomImageLists.last().imageIds[0]), RandomImageLists.last().getId(),RandomImageLists.last().getName(),RandomImageLists.last().getTimeInterval().toString());
    }
    else if (CurrentRandomImageList->getId() > 0)
    {
        UpdateViewTabItem();
        interfaceAddition->ClearConteinerWidget(interfaceAddition->getcontainerWidgetRandomImageListShow());
        CreateViewTabInterface();

    }
}


void TimeTabRandomListWidget::on_TimeTabRandomListTabButtonBox_rejected()
{
    ui->TimeTabRandomListTabWidget->setCurrentIndex(0);
}

