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

        timeTabrRandomListWidget = new TimeTabrRandomListWidget(dbManager,imageManager,this);
        timeTabrRandomListWidget ->show();
        timeTabrRandomListWidget->move(0,100);

      connect(this, &TimeTab::SendSignal, timeTabrRandomListWidget, &TimeTabrRandomListWidget::AddRandomListItem);
}

TimeTab::~TimeTab()
{
    delete ui;
}




void TimeTab::on_TimeTabMenuBarPlusButton_clicked()
{
emit SendSignal();
}

