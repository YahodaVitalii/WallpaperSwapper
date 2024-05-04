#include "timetab.h"
#include "ui_timetab.h"
#include "style.h"

TimeTab::TimeTab(DBManager *dbManager,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTab), dbManager(dbManager)
{
    ui->setupUi(this);

    ui->TimeTabWidget->setStyleSheet(Style::getTabsStyle());
   // ui->TimeTabMenuBar->setStyleSheet(Style::getTimeTabStyle());
        ui->TimeTabMenuBar->setStyleSheet(Style::getMenuBarStyle());
   // ui->StandartTabButtonMenuWidget->setStyleSheet(Style::getStandartTabStyle());
}

TimeTab::~TimeTab()
{
    delete ui;
}




void TimeTab::on_TimeTabMenuBarPlusButton_clicked()
{

}

