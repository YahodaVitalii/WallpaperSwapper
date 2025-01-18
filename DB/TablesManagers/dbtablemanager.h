#ifndef DBTABLEMANAGER_H
#define DBTABLEMANAGER_H

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVector>
#include <QMap>
#include "exception/wsexception.h"

template<typename ValueType, typename ContainerType = QVector<ValueType>>
class DBTableManager
{
public:
    DBTableManager() = default;
    virtual ~DBTableManager() = default;

    virtual bool insertIntoTable(const ValueType& value) = 0;

    virtual ContainerType getAllRecords() = 0;

protected:
    bool executeQuery(QSqlQuery& query) {
        if (!query.exec()) {
            qWarning() << "SQL error:" << query.lastError().text();
            throw WSException(query.lastError().text());
            return false;
        }
        return true;
    }

    bool checkDatabaseConnection() {
        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            qDebug() << "Database is not open. Attempting to open.";
            if (!db.open()) {
                qDebug() << "Failed to open database:" << db.lastError().text();
                return false;
            }
        }
        return true;
    }
};

#endif // DBTABLEMANAGER_H
