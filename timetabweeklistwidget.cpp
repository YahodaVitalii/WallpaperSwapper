#include "timetabweeklistwidget.h"
#include "ui_timetabweeklistwidget.h"

TimeTabWeekListWidget::TimeTabWeekListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTabWeekListWidget)
{
    ui->setupUi(this);
}

TimeTabWeekListWidget::~TimeTabWeekListWidget()
{
    delete ui;
}

void TimeTabWeekListWidget::on_pushButton_clicked()
{

}

