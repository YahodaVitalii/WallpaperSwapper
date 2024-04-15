#ifndef SQLITEDBMANAGER_H
#define SQLITEDBMANAGER_H

#include <QSqlDatabase>
#include "dbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QVector>
#include <QString>

#define DATABASE_HOST_NAME   "WSDataBase"
#define DATABASE_FILE_NAME   "WlapperSwaperDataBase.sqlite"

#define TABLE_IMAGE       "Images"
#define TABLE_IMAGE_ID    "id"
#define TABLE_IMAGE_NAME  "name"
#define TABLE_IMAGE_URL   "url"
#define TABLE_IMAGE_HEIGHT  "hight"
#define TABLE_IMAGE_WIDTH  "width"

class SqliteDBManager : public DBManager {

public:
    static SqliteDBManager* getInstance();
    void connectToDataBase() override;
    QSqlDatabase getDB() override;
    bool insertIntoImageTable(const WlapperImage& wlapperImage) override;
    QVector<WlapperImage> getAllImages() override;
private:

    QSqlDatabase db;

    static SqliteDBManager* instance;

    SqliteDBManager();


    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();
};

#endif // SQLITEDBMANAGER_H
