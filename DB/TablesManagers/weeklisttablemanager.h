#ifndef WEEKLISTTABLEMANAGER_H
#define WEEKLISTTABLEMANAGER_H

#include<QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QVariant>
#include "models/weekimagelist.h"
#include "exception/wsexception.h"
#include "listtablemanager.h"

class WeekListTableManager : public ListTableManager<WeekImageList, QVector<WeekImageList>> {
public:
    WeekListTableManager() = default;
    virtual ~WeekListTableManager() = default;

    bool insertIntoTable(const WeekImageList& weekImageList) override;
    QVector<WeekImageList> getAllRecords() override;
    bool updateList(const WeekImageList& weekImageList) override;
    WeekImageList findListById(int id) override;
};

#endif // WEEKLISTTABLEMANAGER_H
