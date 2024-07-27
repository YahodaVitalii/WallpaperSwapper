#ifndef DBDAYLISTTABLEMANAGER_H
#define DBDAYLISTTABLEMANAGER_H

#include<QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include"dayimagelist.h"
#include "wsexeptions.h"
class DBDayListTableManager
{
public:
    DBDayListTableManager();
    bool insertDayImageList(DayImageList* dayImageList);
    bool updateDayImageList(DayImageList* dayImageList);
    QVector<DayImageList> getAllDayImageLists();
    DayImageList findDayImageListById(int id);
};

#endif // DBDAYLISTTABLEMANAGER_H
