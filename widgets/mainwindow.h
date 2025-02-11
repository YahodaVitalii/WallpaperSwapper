#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include "standarttab.h"
#include "timetab.h"
#include "moodtab.h"
#include "DB/dbmanager.h"
#include "DB/sqlitedbmanager.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE
class QSqlTableModel;

class DBManager;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void PaintEvent(QPaintEvent *event);
private slots:
    void on_mainMenuStandartButton_clicked();

    void on_mainMenuTimeButton_clicked();

    void on_mainMenuMoodButton_clicked();

private:
    Ui::MainWindow *ui;
    StandartTab* standartTab;
    TimeTab* timeTab;
    MoodTab* moodTab;

    InterfaceAddition* interfaceAddition;
    UIElementFactory* uiElementFactory;
    ImageList* imageList;

    void setInterfaceStyle();
};
#endif // MAINWINDOW_H
