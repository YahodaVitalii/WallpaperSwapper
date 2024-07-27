#ifndef DBRANDOMLISTTABLEMANAGER_H
#define DBRANDOMLISTTABLEMANAGER_H

#include<QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include"randomimagelist.h"
#include "wsexeptions.h"
class DBRandomListTableManager
{
public:
    DBRandomListTableManager();
    bool insertImageList(RandomImageList* imageList);
    bool updateRandomImageList(RandomImageList* randomImageList);
    QVector<RandomImageList> getAllRandomImageLists();
    RandomImageList FindRandomImageListById(int id);
};

#endif // DBRANDOMLISTTABLEMANAGER_H
