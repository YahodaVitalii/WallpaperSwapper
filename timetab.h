#ifndef TIMETAB_H
#define TIMETAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include "sqlitedbmanager.h"
#include "imagelist.h"
#include "style.h"
#include "timetabrandomlistwidget.h"
#include "timetabweeklistwidget.h"
#include "timetabdaylistwidget.h"
namespace Ui {
class TimeTab;
}

class TimeTab : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTab(DBManager* dbManager, ImageList* imageList, DialogWindowListOfImage *dialogWindowListOfImage, QWidget *parent = nullptr);
    ~TimeTab();

    TimeTabRandomListWidget* getTimeTabRandomListWidget() const;
    TimeTabWeekListWidget* getTimeTabWeekListWidget() const;
    TimeTabDayListWidget* getTimeTabDayListWidget() const;
private slots:


    void on_TimeTabMenuBarPlusButton_clicked();


    void on_TimeTabMenuBarRandomButton_clicked();

    void on_TimeTabMenuBarWeekButton_clicked();

    void on_TimeTabMenuBarDayButton_clicked();

signals:
    void SendSignalForRandomListWidget();
    void SendSignalForWeekListWidget();
    void SendSignalForDayListWidget();
private:
    Ui::TimeTab *ui;
    DBManager* dbManager;
    ImageList* imageList;
    DialogWindowListOfImage *dialogWindowListOfImage;

    TimeTabRandomListWidget* timeTabRandomListWidget;
    TimeTabWeekListWidget* timeTabWeekListWidget;
    TimeTabDayListWidget*  timeTabDayListWidget;

    void CreateimeTabRandomListWidget();
    void CreateTimeTabWeekListWidget();
    void CreateTimeTabDayListWidget();

    void showTab(QWidget* tab);
};

#endif // TIMETAB_H
