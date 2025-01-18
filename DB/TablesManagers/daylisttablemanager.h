#ifndef DAYLISTTABLEMANAGER_H
#define DAYLISTTABLEMANAGER_H

#include <QVector>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "models/dayimagelist.h"
#include "exception/wsexception.h"
#include "listtablemanager.h"

class DayListTableManager : public ListTableManager<DayImageList, QVector<DayImageList>> {
public:
    DayListTableManager();
    bool insertIntoTable(const DayImageList& dayImageList) override;
    QVector<DayImageList> getAllRecords() override;
    bool updateList(const DayImageList& dayImageList) override;
    DayImageList findListById(int id) override;
};

#endif // DAYLISTTABLEMANAGER_H
