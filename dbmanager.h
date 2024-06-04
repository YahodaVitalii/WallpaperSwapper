
#ifndef DBMANAGER_H
#define DBMANAGER_H
#include <QSqlDatabase>
#include "wlapperimage.h"
#include "randomimagelist.h"
#include "weekimagelist.h"
class DBManager {
public:

    virtual void connectToDataBase() = 0;

    virtual QSqlDatabase getDB() = 0;

    virtual bool insertIntoImageTable(const WlapperImage& wlapperImage)=0;
    virtual QVector<WlapperImage> getAllImages() = 0;
    virtual bool deleteImageById(int imageId)=0;
    virtual bool insertImageList(RandomImageList* imageList)=0;
    virtual QVector<RandomImageList> getAllRandomImageLists()=0;
    virtual RandomImageList FindRandomImageListById(int id) =0;
    virtual bool updateRandomImageList(RandomImageList* randomImageList)=0;
    virtual  bool updateWeekImageList(WeekImageList* weekImageList) = 0;
    virtual WeekImageList findWeekImageListById(int id) =0;
    virtual QVector<WeekImageList> getAllWeekImageLists() =0;
    virtual bool insertWeekImageList(WeekImageList* weekImageList) =0;
};

#endif // DBMANAGER_H
