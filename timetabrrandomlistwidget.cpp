#include "timetabrrandomlistwidget.h"
#include "ui_timetabrrandomlistwidget.h"

TimeTabrRandomListWidget::TimeTabrRandomListWidget(DBManager* dbManager, ImageManager *imageManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTabrRandomListWidget),dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);
       interfaceAddition = new InterfaceAddition(this, dbManager, imageManager);

       // Використання функції CreateScrollArea для створення QScrollArea
       interfaceAddition->CreateScrollArea(ui->CreateTab, interfaceAddition->getContainerWidgetRandomImageListCreate(),640,280,0,60);
       ui->TimeTabrRandomListTabWidget->tabBar()->hide();
       CreateDialogWindowListOfImage();

//    scrollArea = new QScrollArea(ui->CreateTab);
//    scrollArea->setFixedSize(640, 280);
//    scrollArea->move(0, 60);
//    scrollArea->setWidgetResizable(true);
//    scrollArea->setWidget(interfaceAddition->getContainerWidgetRandomImageListCreate());
}

TimeTabrRandomListWidget::~TimeTabrRandomListWidget()
{
    delete ui;
}

void TimeTabrRandomListWidget::CreateDialogWindowListOfImage()
{
    dialogWindowListOfImage = new DialogWindowListOfImage(this->dbManager,imageManager,interfaceAddition, this);
    connect(interfaceAddition, &InterfaceAddition::imageSelected, this, &TimeTabrRandomListWidget::addImageInList);
    dialogWindowListOfImage->setStyleSheet(Style::getTabsStyle());
}

void TimeTabrRandomListWidget::ShowDialogWindowListOfImage()
{
    dialogWindowListOfImage ->show();
}

void TimeTabrRandomListWidget::AddRandomListItem()
{
    ui->timeEditTimeInterval->setTime(QTime(0, 0));
    currentImageIds.clear();
    interfaceAddition->ClearConteinerWidget(interfaceAddition->getContainerWidgetRandomImageListCreate());
    ui->TimeTabrRandomListTabWidget->setCurrentIndex(1);
}


void TimeTabrRandomListWidget::on_ButtonAddNewItemOfRandomList_clicked()
{
    ShowDialogWindowListOfImage();
}

void TimeTabrRandomListWidget::addImageInList(int index) {
    interfaceAddition->CreateRandomListOfImageItem(index);
    currentImageIds.append(imageManager->GetImageByIndex(index).getId());
    dialogWindowListOfImage ->hide();
}



void TimeTabrRandomListWidget::on_TimeTabrRandomListTabButtonBox_accepted()
{
    RandomImageList* randomImageList = new RandomImageList(ui->timeEditTimeInterval->dateTime(),currentImageIds);
    dbManager->insertImageList(randomImageList);
    ui->TimeTabrRandomListTabWidget->setCurrentIndex(0);
}


void TimeTabrRandomListWidget::on_TimeTabrRandomListTabButtonBox_rejected()
{
    ui->TimeTabrRandomListTabWidget->setCurrentIndex(0);
}

