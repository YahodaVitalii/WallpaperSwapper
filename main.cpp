#include "widgets/mainwindow.h"
#include "sqlitedbmanager.h"
#include <QApplication>
#include <QPainterPath>
#include <QRegion>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DBManager* dbManager = SqliteDBManager::getInstance();

    dbManager->connectToDataBase();

    MainWindow w(dbManager);
    w.show();
    return a.exec();
}
