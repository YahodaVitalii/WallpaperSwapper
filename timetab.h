#ifndef TIMETAB_H
#define TIMETAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include "sqlitedbmanager.h"
namespace Ui {
class TimeTab;
}

class TimeTab : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTab(DBManager* dbManager,QWidget *parent = nullptr);
    ~TimeTab();

private slots:


private:
    Ui::TimeTab *ui;
    DBManager* dbManager;

};

#endif // TIMETAB_H
