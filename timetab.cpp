#include "timetab.h"
#include "ui_timetab.h"

TimeTab::TimeTab(DBManager *dbManager,ImageManager* imageManager,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTab), dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);
    ui->TimeTabWidget->setStyleSheet(Style::getTabsStyle());
    ui->TimeTabMenuBar->setStyleSheet(Style::getMenuBarStyle());
    CreateimeTabRandomListWidget();
     //CreateTimeTabWeekListWidget();
    //CreateTimeTabDayListWidget();
}

TimeTab::~TimeTab()
{
    delete ui;
}

void TimeTab::CreateimeTabRandomListWidget()
{
    timeTabRandomListWidget = new TimeTabRandomListWidget(dbManager,imageManager,this);
    timeTabRandomListWidget->move(10,100);
    timeTabRandomListWidget->setStyleSheet(Style::getTimeTabStyle());
    timeTabRandomListWidget ->show();
    connect(this, &TimeTab::SendSignalForRandomListWidget, timeTabRandomListWidget, &TimeTabRandomListWidget::AddRandomListItem);
}

void TimeTab::CreateTimeTabWeekListWidget()
{
    timeTabWeekListWidget = new TimeTabWeekListWidget(dbManager,imageManager,this);
    timeTabWeekListWidget->move(10,100);
    timeTabWeekListWidget->setStyleSheet(Style::getTimeTabStyle());
    timeTabWeekListWidget ->show();
    connect(this, &TimeTab::SendSignalForWeekListWidget, timeTabWeekListWidget, &TimeTabWeekListWidget::AddWeekListItem);
}

void TimeTab::CreateTimeTabDayListWidget()
{
    timeTabDayListWidget = new TimeTabDayListWidget(dbManager,imageManager,this);
    timeTabDayListWidget->move(10,100);
    timeTabDayListWidget->setStyleSheet(Style::getTimeTabStyle());
    timeTabDayListWidget ->show();
    connect(this, &TimeTab::SendSignalForDayListWidget, timeTabDayListWidget, &TimeTabDayListWidget::AddDayListItem);
}

void TimeTab::on_TimeTabMenuBarPlusButton_clicked()
{
    emit SendSignalForRandomListWidget();
    emit SendSignalForWeekListWidget();
    emit SendSignalForDayListWidget();
}


