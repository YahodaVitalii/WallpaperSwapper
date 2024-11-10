
#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include "wallpaperimage.h"
#include "randomimagelist.h"
#include "weekimagelist.h"
#include "dayimagelist.h"
class DBManager {
public:

    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;

};

#endif // DBMANAGER_H
