#ifndef TIMETAB_H
#define TIMETAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include "sqlitedbmanager.h"
#include "imagelist.h"
#include "GUI/style/style.h"
#include "randomlistwidget.h"
#include "weeklistwidget.h"
#include "daylistwidget.h"
#include "baselistwidget.h"
#include "GUI/service/tabwidgetfactory.h"
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

    void on_TimeTabMenuBarCurrentListButton_clicked();
public slots:
  void  SetActiveImageList(BaseImageList* imageList);
signals:
    void CreateNewList();
private:

    Ui::TimeTab *ui;

    TimeTabChildrenWidget* currentTab;

    RandomTabWidgetFactory randomTabWidgetFactory;
    WeekTabWidgetFactory weekTabWidgetFactory;
    DayTabWidgetFactory dayTabWidgetFactory;

    BaseImageList* activeImageList;

    void createChildTab(TabWidgetFactory& factory);
};

#endif // TIMETAB_H
