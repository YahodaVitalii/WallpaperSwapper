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

#define TABLE_RANDOM_IMAGE_LIST

class SqliteDBManager : public DBManager {

public:
    static SqliteDBManager* getInstance();
    void connectToDataBase() override;
    QSqlDatabase getDB() override;

    bool insertIntoImageTable(const WlapperImage& wlapperImage) override;
    QVector<WlapperImage> getAllImages() override;
    bool deleteImageById(int imageId) override;
    bool insertImageList(RandomImageList *imageList) override;
    bool insertWeekImageList(WeekImageList* weekImageList) override;
    bool SqliteDBManager::insertDayImageList(DayImageList* dayImageList) override;
    QVector<RandomImageList> getAllRandomImageLists() override;
    QVector<WeekImageList> getAllWeekImageLists() override;
    QVector<DayImageList> getAllDayImageLists() override;
    RandomImageList FindRandomImageListById(int id) override;
    WeekImageList findWeekImageListById(int id) override;
    DayImageList findDayImageListById(int id) override;
    bool updateRandomImageList(RandomImageList* randomImageList) override;
    bool updateWeekImageList(WeekImageList* weekImageList) override;
    bool updateDayImageList(DayImageList* dayImageList) override;

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
