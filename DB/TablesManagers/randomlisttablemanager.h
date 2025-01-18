#ifndef RANDOMLISTTABLEMANAGER_H
#define RANDOMLISTTABLEMANAGER_H

#include "listtablemanager.h"
#include "models/randomimagelist.h"
#include "exception/wsexception.h"
#include <QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

class RandomListTableManager : public ListTableManager<RandomImageList, QVector<RandomImageList>> {
public:
    RandomListTableManager() = default;
    bool insertIntoTable(const RandomImageList& imageList) override;
    bool updateList(const RandomImageList& randomImageList) override;
    QVector<RandomImageList> getAllRecords() override;
    RandomImageList findListById(int id) override;
    QVector<int> getImageIdsForList(int listId) const;
};

#endif // RANDOMLISTTABLEMANAGER_H
