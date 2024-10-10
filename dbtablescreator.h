#ifndef DBTABLESCREATOR_H
#define DBTABLESCREATOR_H
#include <QSqlQuery>
#include <QDebug>
#include "wsexception.h"
#include <QSqlError>
class DBTablesCreator
{
public:
    bool BuildTables();
private:
    void createTableImage();
    void createTableRandomImageLists();
    void createTableWeekImageLists();
    void createTableDayImageLists();
    void createTableRandomImages();
    void createTableWeekImages();
    void createTableDayImages();
    void createTableMoodImage();
   void  createTableEmodji();
};


#endif // DBTABLESCREATOR_H
