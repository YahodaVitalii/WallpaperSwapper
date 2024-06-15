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

 interfaceAddition->CreateScrollArea(ui->CreateTab, interfaceAddition->getcontainerWidgetDayImageListCreate(),600,280,0,60);
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

void TimeTabDayListWidget::AddDayListItem()
{
    ui->TimeTabDayListTabWidget->setCurrentIndex(1);
}

void TimeTabDayListWidget::addImageInList(int index)
{
interfaceAddition->CreateDayListOfImageItem( index);

dialogWindowListOfImage ->hide();

}

void TimeTabDayListWidget::on_ButtonAddNewItemOfDayList_clicked()
{
   dialogWindowListOfImage->show();
}


void TimeTabDayListWidget::on_TimeTabDayListTabButtonBox_accepted()
{
    ui->TimeTabDayListTabWidget->setCurrentIndex(0);
}


void TimeTabDayListWidget::on_TimeTabDayListTabButtonBox_rejected()
{
    ui->TimeTabDayListTabWidget->setCurrentIndex(0);
}

