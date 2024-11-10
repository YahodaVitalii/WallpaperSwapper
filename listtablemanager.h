#ifndef LISTTABLEMANAGER_H
#define LISTTABLEMANAGER_H

#include "dbtablemanager.h"

template<typename ValueType, typename ContainerType = QVector<T>>
class ListTableManager : public DBTableManager<ValueType, ContainerType> {
public:
    ListTableManager() = default;
    virtual ~ListTableManager() = default;

    virtual bool insertIntoTable(const ValueType& imageList) override = 0;
    virtual ContainerType getAllRecords() override = 0;
    virtual bool updateList(const ValueType& imageList) = 0;
    virtual ValueType findListById(int id) = 0;
};

#endif // LISTTABLEMANAGER_H
