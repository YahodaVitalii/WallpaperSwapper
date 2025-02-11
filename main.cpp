#include "widgets/mainwindow.h"
#include "DB/sqlitedbmanager.h"
#include "core/appcoreservice.h"
#include <QApplication>
#include <QPainterPath>
#include <QRegion>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBManager* dbManager = SqliteDBManager::getInstance();
    dbManager->connectToDataBase();
   // AppCoreService appCoreService;

    MainWindow w;
    w.show();
    return a.exec();
}
