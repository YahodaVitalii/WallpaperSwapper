#include "timetab.h"
#include "ui_timetab.h"

TimeTab::TimeTab(DBManager *dbManager, ImagesList *imageManager,DialogWindowListOfImage* dialogWindowListOfImage, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTab), dbManager(dbManager),imageManager(imageManager),dialogWindowListOfImage(dialogWindowListOfImage)
{
    ui->setupUi(this);
    ui->TimeTabWidget->setStyleSheet(Style::getTabsStyle());
    ui->TimeTabMenuBar->setStyleSheet(Style::getMenuBarStyle());
    CreateimeTabRandomListWidget();
    CreateTimeTabWeekListWidget();
    CreateTimeTabDayListWidget();

    showTab(timeTabRandomListWidget);
}

TimeTab::~TimeTab()
{
    delete ui;
}

TimeTabRandomListWidget *TimeTab::getTimeTabRandomListWidget() const
{
    return timeTabRandomListWidget;
}

TimeTabWeekListWidget *TimeTab::getTimeTabWeekListWidget() const
{
    return timeTabWeekListWidget;
}

TimeTabDayListWidget *TimeTab::getTimeTabDayListWidget() const
{
    return timeTabDayListWidget;
}

void TimeTab::CreateimeTabRandomListWidget()
{
    timeTabRandomListWidget = new TimeTabRandomListWidget(dbManager,imageManager,dialogWindowListOfImage,this);
    timeTabRandomListWidget->move(10,100);
    timeTabRandomListWidget->setStyleSheet(Style::getTimeTabStyle());
    //timeTabRandomListWidget ->show();
    connect(this, &TimeTab::SendSignalForRandomListWidget, timeTabRandomListWidget, &TimeTabRandomListWidget::AddRandomListItem);

}

void TimeTab::CreateTimeTabWeekListWidget()
{
    timeTabWeekListWidget = new TimeTabWeekListWidget(dbManager,imageManager,dialogWindowListOfImage, this);
    timeTabWeekListWidget->move(10,100);
    timeTabWeekListWidget->setStyleSheet(Style::getTimeTabStyle());
    // timeTabWeekListWidget ->show();
    connect(this, &TimeTab::SendSignalForWeekListWidget, timeTabWeekListWidget, &TimeTabWeekListWidget::AddWeekListItem);
}

void TimeTab::CreateTimeTabDayListWidget()
{
    timeTabDayListWidget = new TimeTabDayListWidget(dbManager,imageManager,dialogWindowListOfImage,this);
    timeTabDayListWidget->move(10,100);
    timeTabDayListWidget->setStyleSheet(Style::getTimeTabStyle());
    //timeTabDayListWidget ->show();
    connect(this, &TimeTab::SendSignalForDayListWidget, timeTabDayListWidget, &TimeTabDayListWidget::AddDayListItem);
}

void TimeTab::showTab(QWidget *tab)
{
    timeTabRandomListWidget->hide();
    timeTabWeekListWidget->hide();
    timeTabDayListWidget->hide();

    tab->show();
}

void TimeTab::on_TimeTabMenuBarPlusButton_clicked()
{
    emit SendSignalForRandomListWidget();
    emit SendSignalForWeekListWidget();
    emit SendSignalForDayListWidget();
}



void TimeTab::on_TimeTabMenuBarRandomButton_clicked()
{
    showTab(timeTabRandomListWidget);
}


void TimeTab::on_TimeTabMenuBarWeekButton_clicked()
{
    showTab(timeTabWeekListWidget);
}


void TimeTab::on_TimeTabMenuBarDayButton_clicked()
{
    showTab(timeTabDayListWidget);
}

