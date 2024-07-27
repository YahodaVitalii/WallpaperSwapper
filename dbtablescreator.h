#ifndef DBTABLESCREATOR_H
#define DBTABLESCREATOR_H
#include <QSqlQuery>
#include <QDebug>
#include "wsexeptions.h"
#include <QSqlError>
class DBTablesCreator
{
public:
    bool BuildTables();
private:
    void createTableImage();
    void createTableRandomImageLists();
    void createTableWeekImages();
    void createTableDayImages();
};


#endif // DBTABLESCREATOR_H
