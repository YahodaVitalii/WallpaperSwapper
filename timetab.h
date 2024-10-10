#ifndef TIMETAB_H
#define TIMETAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include "sqlitedbmanager.h"
#include "imagelist.h"
#include "style.h"
#include "randomlistwidget.h"
#include "weeklistwidget.h"
#include "daylistwidget.h"
#include "baselistwidget.h"
#include "tabwidgetfactory.h"
namespace Ui {
class TimeTab;
}

class TimeTab : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTab(QWidget *parent = nullptr);
    ~TimeTab();

private slots:
    void on_TimeTabMenuBarPlusButton_clicked();

    void on_TimeTabMenuBarRandomButton_clicked();
    void on_TimeTabMenuBarWeekButton_clicked();
    void on_TimeTabMenuBarDayButton_clicked();

signals:
    void CreateNewList();
private:

    Ui::TimeTab *ui;

    TimeTabWidgets* currentTab;

    RandomTabWidgetFactory randomTabWidgetFactory;
    WeekTabWidgetFactory weekTabWidgetFactory;
    DayTabWidgetFactory dayTabWidgetFactory;

    void createChildTab(TabWidgetFactory& factory);
};

#endif // TIMETAB_H
