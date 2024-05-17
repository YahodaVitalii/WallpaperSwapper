#ifndef TIMETABWEEKLISTWIDGET_H
#define TIMETABWEEKLISTWIDGET_H

#include <QWidget>

namespace Ui {
class TimeTabWeekListWidget;
}

class TimeTabWeekListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TimeTabWeekListWidget(QWidget *parent = nullptr);
    ~TimeTabWeekListWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::TimeTabWeekListWidget *ui;
};

#endif // TIMETABWEEKLISTWIDGET_H
