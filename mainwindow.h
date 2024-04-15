#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "standarttab.h"
#include "dbmanager.h"
#include "sqlitedbmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE
class QSqlTableModel;

class DBManager;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DBManager* dbManrage, QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void PaintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    StandartTab* standartTab;

    DBManager* dbManager;
    QSqlTableModel* model;

    void setInterfaceStyle();
};
#endif // MAINWINDOW_H
