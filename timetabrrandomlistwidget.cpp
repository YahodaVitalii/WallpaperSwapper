#include "timetabrrandomlistwidget.h"
#include "ui_timetabrrandomlistwidget.h"

TimeTabrRandomListWidget::TimeTabrRandomListWidget(DBManager* dbManage, ImageManager *imageManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTabrRandomListWidget),dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);
}

TimeTabrRandomListWidget::~TimeTabrRandomListWidget()
{
    delete ui;
}

void TimeTabrRandomListWidget::on_ButtonAddNewItemOfRandomList_clicked()
{

}

