#include "timetab.h"
#include "ui_timetab.h"

TimeTab::TimeTab( QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTab),currentTab(nullptr)
{
    ui->setupUi(this);
    ui->TimeTabWidget->setStyleSheet(Style::getTabsStyle());
    ui->TimeTabMenuBar->setStyleSheet(Style::getMenuBarStyle());

    createChildTab(randomTabWidgetFactory);
}

TimeTab::~TimeTab()
{
    delete ui;
}

void TimeTab::createChildTab(TabWidgetFactory &factory)
{
    if (currentTab != nullptr) {
           delete currentTab;  // Видалити попередню вкладку, якщо вона існує
           currentTab = nullptr;
       }

    TimeTabChildrenWidget* tab = factory.createWidget(this);

        if (currentTab != nullptr) {
            currentTab->hide();
        }

        currentTab = tab;
        tab->show();
        connect(this, &TimeTab::CreateNewList, currentTab, &TimeTabChildrenWidget::CreateViewListItem);
         connect(currentTab, &TimeTabChildrenWidget::resendListSignal, this, &TimeTab::SetActiveImageList);
}

void TimeTab::on_TimeTabMenuBarPlusButton_clicked()
{
    emit CreateNewList();
}


void TimeTab::on_TimeTabMenuBarRandomButton_clicked()
{
   createChildTab(randomTabWidgetFactory);
}


void TimeTab::on_TimeTabMenuBarWeekButton_clicked()
{
    createChildTab(weekTabWidgetFactory);
}

void TimeTab::on_TimeTabMenuBarDayButton_clicked()
{
    createChildTab(dayTabWidgetFactory);
}

void TimeTab::on_TimeTabMenuBarCurrentListButton_clicked()
{

}

void TimeTab::SetActiveImageList(BaseImageList *imageList)
{
    activeImageList = imageList;
   qDebug()<< activeImageList->getName();
}

