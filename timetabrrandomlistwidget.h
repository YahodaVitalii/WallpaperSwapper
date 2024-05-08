#ifndef TIMETABRRANDOMLISTWIDGET_H
#define TIMETABRRANDOMLISTWIDGET_H
#include "sqlitedbmanager.h"
#include <QWidget>
#include "imagemanager.h"
namespace Ui {
class TimeTabrRandomListWidget;
}

class TimeTabrRandomListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTabrRandomListWidget(DBManager* dbManage, ImageManager *imageManager, QWidget *parent = nullptr);
    ~TimeTabrRandomListWidget();

private slots:
    void on_ButtonAddNewItemOfRandomList_clicked();

private:
    Ui::TimeTabrRandomListWidget *ui;
    DBManager* dbManager;
    ImageManager *imageManager;
};

#endif // TIMETABRRANDOMLISTWIDGET_H
