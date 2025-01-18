
#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include "models/wallpaperimage.h"
class DBManager {
public:

    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;

};

#endif // DBMANAGER_H
