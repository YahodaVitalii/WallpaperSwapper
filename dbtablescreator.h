#ifndef DBTABLESCREATOR_H
#define DBTABLESCREATOR_H
#include <QSqlQuery>
#include <QDebug>
#include "wsexeptions.h"
#include <QSqlError>
#include <QFile>
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
    void createTableMoodImageList();
   void  createTableEmodji();
};


#endif // DBTABLESCREATOR_H
