#include "dbdaylisttablemanager.h"

DBDayListTableManager::DBDayListTableManager(){}
bool DBDayListTableManager::insertDayImageList(DayImageList* dayImageList) {
    try {
        if (!dayImageList) {
            throw WSExceptions("Null pointer received for day image list!");
        }

        // Insert the basic list information into DayImageList table
        QSqlQuery query;
        query.prepare("INSERT INTO DayImageList (name) VALUES (:name)");
        query.bindValue(":name", dayImageList->getName());

        if (!query.exec()) {
            throw WSExceptions("Error inserting day image list into DayImageList: " + query.lastError().text());
        }

        // Get the last inserted ID and set it in the non-const object
        int listId = query.lastInsertId().toInt();
        dayImageList->setId(listId);

        // Insert each TimeRangeImage into the DayImages table
        for (const auto& timeRangeImage : dayImageList->getImages()) {
            QSqlQuery imageQuery;
            imageQuery.prepare("INSERT INTO DayImages (timeStart, timeEnd, imageID, listId) "
                               "VALUES (:timeStart, :timeEnd, :imageID, :listId)");
            imageQuery.bindValue(":timeStart", timeRangeImage.startTime);
            imageQuery.bindValue(":timeEnd", timeRangeImage.endTime);
            imageQuery.bindValue(":imageID", timeRangeImage.imageId);
            imageQuery.bindValue(":listId", listId);

            if (!imageQuery.exec()) {
                throw WSExceptions("Error inserting day images into DayImages: " + imageQuery.lastError().text());
            }
        }

        return true;
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

QVector<DayImageList> DBDayListTableManager::getAllDayImageLists() {
    QVector<DayImageList> dayImageLists;

    try {
        // Retrieve all lists from DayImageList
        QSqlQuery query;
        if (!query.exec("SELECT id, name FROM DayImageList")) {
            throw WSExceptions("Error retrieving all day image lists: " + query.lastError().text());
        }

        while (query.next()) {
            int listId = query.value(0).toInt();
            QString name = query.value(1).toString();

            DayImageList dayImageList;
            dayImageList.setId(listId);
            dayImageList.setName(name);

            // Retrieve images associated with this list from DayImages
            QSqlQuery imageQuery;
            imageQuery.prepare("SELECT id, timeStart, timeEnd, imageID FROM DayImages WHERE listId = :listId");
            imageQuery.bindValue(":listId", listId);

            if (!imageQuery.exec()) {
                throw WSExceptions("Error retrieving day images for list: " + imageQuery.lastError().text());
            }

            QVector<TimeRangeImage> images;
            while (imageQuery.next()) {
                TimeRangeImage timeRangeImage;
                timeRangeImage.id = imageQuery.value(0).toInt();
                timeRangeImage.startTime = imageQuery.value(1).toString();
                timeRangeImage.endTime = imageQuery.value(2).toString();
                timeRangeImage.imageId = imageQuery.value(3).toInt();

                images.append(timeRangeImage);
            }

            dayImageList.setImages(images);
            dayImageLists.append(dayImageList);
        }
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return dayImageLists;
}

DayImageList DBDayListTableManager::findDayImageListById(int id) {
    try {
        // Retrieve the list information from DayImageList
        QSqlQuery query;
        query.prepare("SELECT id, name FROM DayImageList WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSExceptions("Error retrieving day image list: " + query.lastError().text());
        }

        if (query.next()) {
            int listId = query.value(0).toInt();
            QString name = query.value(1).toString();

            DayImageList dayImageList;
            dayImageList.setId(listId);
            dayImageList.setName(name);

            // Retrieve images associated with this list from DayImages
            QSqlQuery imageQuery;
            imageQuery.prepare("SELECT id, timeStart, timeEnd, imageID FROM DayImages WHERE listId = :listId");
            imageQuery.bindValue(":listId", listId);

            if (!imageQuery.exec()) {
                throw WSExceptions("Error retrieving day images for list: " + imageQuery.lastError().text());
            }

            QVector<TimeRangeImage> images;
            while (imageQuery.next()) {
                TimeRangeImage timeRangeImage;
                timeRangeImage.id = imageQuery.value(0).toInt();
                timeRangeImage.startTime = imageQuery.value(1).toString();
                timeRangeImage.endTime = imageQuery.value(2).toString();
                timeRangeImage.imageId = imageQuery.value(3).toInt();

                images.append(timeRangeImage);
            }

            dayImageList.setImages(images);
            return dayImageList;
        }
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return DayImageList(); // Return a default-constructed DayImageList if no record with such id is found
}

bool DBDayListTableManager::updateDayImageList(DayImageList* dayImageList) {
    try {
        if (!dayImageList) {
            throw WSExceptions("Null pointer received for day image list!");
        }

        if (dayImageList->getId() == -1) {
            throw WSExceptions("Unknown id for day image list!");
        }

        // Update the basic list information in DayImageList table
        QSqlQuery query;
        query.prepare("UPDATE DayImageList SET name = :name WHERE id = :id");
        query.bindValue(":name", dayImageList->getName());
        query.bindValue(":id", dayImageList->getId());

        if (!query.exec()) {
            throw WSExceptions("Error updating day image list: " + query.lastError().text());
        }

        // Remove existing entries in DayImages associated with this list
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM DayImages WHERE listId = :listId");
        deleteQuery.bindValue(":listId", dayImageList->getId());

        if (!deleteQuery.exec()) {
            throw WSExceptions("Error deleting old day images: " + deleteQuery.lastError().text());
        }

        // Re-insert each TimeRangeImage into the DayImages table
        for (const auto& timeRangeImage : dayImageList->getImages()) {
            QSqlQuery imageQuery;
            imageQuery.prepare("INSERT INTO DayImages (timeStart, timeEnd, imageID, listId) "
                               "VALUES (:timeStart, :timeEnd, :imageID, :listId)");
            imageQuery.bindValue(":timeStart", timeRangeImage.startTime);
            imageQuery.bindValue(":timeEnd", timeRangeImage.endTime);
            imageQuery.bindValue(":imageID", timeRangeImage.imageId);
            imageQuery.bindValue(":listId", dayImageList->getId());

            if (!imageQuery.exec()) {
                throw WSExceptions("Error inserting day images into DayImages: " + imageQuery.lastError().text());
            }
        }

        return true;
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}
