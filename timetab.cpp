#include "timetab.h"
#include "ui_timetab.h"

TimeTab::TimeTab(DBManager *dbManager,ImageManager* imageManager,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTab), dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);

    ui->TimeTabWidget->setStyleSheet(Style::getTabsStyle());
   // ui->TimeTabMenuBar->setStyleSheet(Style::getTimeTabStyle());
        ui->TimeTabMenuBar->setStyleSheet(Style::getMenuBarStyle());
   // ui->StandartTabButtonMenuWidget->setStyleSheet(Style::getStandartTabStyle());

        timeTabRandomListWidget = new TimeTabRandomListWidget(dbManager,imageManager,this);
        timeTabRandomListWidget->move(10,100);
        timeTabRandomListWidget->setStyleSheet(Style::getTimeTabStyle());
        timeTabRandomListWidget ->show();


      connect(this, &TimeTab::SendSignal, timeTabRandomListWidget, &TimeTabRandomListWidget::AddRandomListItem);

}

TimeTab::~TimeTab()
{
    delete ui;
}




void TimeTab::on_TimeTabMenuBarPlusButton_clicked()
{
emit SendSignal();
}

