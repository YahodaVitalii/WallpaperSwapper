#ifndef DBWEEKLISTTABLEMANAGER_H
#define DBWEEKLISTTABLEMANAGER_H

#include<QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QVariant>
#include"weekimagelist.h"
#include "wsexeptions.h"
class DBWeekListTableManager
{
public:
    bool insertWeekImageList(WeekImageList* weekImageList);
    bool updateWeekImageList(WeekImageList* weekImageList);
    QVector<WeekImageList> getAllWeekImageLists();
    WeekImageList findWeekImageListById(int id);
};

#endif // DBWEEKLISTTABLEMANAGER_H
