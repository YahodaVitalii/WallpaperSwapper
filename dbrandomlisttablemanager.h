#ifndef DBRANDOMLISTTABLEMANAGER_H
#define DBRANDOMLISTTABLEMANAGER_H

#include<QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include"randomimagelist.h"
#include "wsexception.h"
class DBRandomListTableManager
{
public:
    bool insertImageList(RandomImageList* imageList);
    bool updateRandomImageList(RandomImageList* randomImageList);
    QVector<RandomImageList> getAllRandomImageLists();
    RandomImageList FindRandomImageListById(int id);
    QVector<int> getImageIdsForList(int listId) const;
};

#endif // DBRANDOMLISTTABLEMANAGER_H
