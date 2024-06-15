#ifndef TIMETAB_H
#define TIMETAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include "sqlitedbmanager.h"
#include "imagemanager.h"
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
    explicit TimeTab(DBManager* dbManager,ImageManager* imageManager,QWidget *parent = nullptr);
    ~TimeTab();
    void CreateimeTabRandomListWidget();
    void CreateTimeTabWeekListWidget();
    void CreateTimeTabDayListWidget();

private slots:


    void on_TimeTabMenuBarPlusButton_clicked();


signals:
    void SendSignalForRandomListWidget();
    void SendSignalForWeekListWidget();
    void SendSignalForDayListWidget();
private:
    Ui::TimeTab *ui;
    DBManager* dbManager;
    ImageManager* imageManager;

    TimeTabRandomListWidget* timeTabRandomListWidget;
    TimeTabWeekListWidget* timeTabWeekListWidget;
    TimeTabDayListWidget*  timeTabDayListWidget;

};

#endif // TIMETAB_H
