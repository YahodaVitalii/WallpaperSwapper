#ifndef TIMETAB_H
#define TIMETAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include "sqlitedbmanager.h"
#include "imagemanager.h"
#include "style.h"
#include "timetabrrandomlistwidget.h"
namespace Ui {
class TimeTab;
}

class TimeTab : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTab(DBManager* dbManager,ImageManager* imageManager,QWidget *parent = nullptr);
    ~TimeTab();

private slots:


    void on_TimeTabMenuBarPlusButton_clicked();
signals:
    void SendSignal();
private:
    Ui::TimeTab *ui;
    DBManager* dbManager;
    ImageManager* imageManager;

    TimeTabrRandomListWidget* timeTabrRandomListWidget;
};

#endif // TIMETAB_H
