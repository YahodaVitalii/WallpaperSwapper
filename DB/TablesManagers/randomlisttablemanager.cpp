#include "randomlisttablemanager.h"
bool RandomListTableManager::insertIntoTable(const RandomImageList& imageList) {
    try {
        QSqlQuery query;
        query.prepare("INSERT INTO RandomImageLists (name, time_interval) VALUES (:name, :time)");
        query.bindValue(":name", imageList.getName());
        query.bindValue(":time", imageList.getTimeInterval());

        if (!query.exec()) {
            throw WSException("Error inserting image list: " + query.lastError().text());
        }

        int listId = query.lastInsertId().toInt();

        for (int imageId : imageList.getImageIds()) {
            QSqlQuery imageQuery;
            imageQuery.prepare("INSERT INTO RandomImages (random_list_id, image_id) VALUES (:listId, :imageId)");
            imageQuery.bindValue(":listId", listId);
            imageQuery.bindValue(":imageId", imageId);

            if (!imageQuery.exec()) {
                throw WSException("Error inserting image: " + imageQuery.lastError().text());
            }
        }
        return true;
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

// Retrieve all random image lists
QVector<RandomImageList> RandomListTableManager::getAllRecords() {
    QVector<RandomImageList> randomImageLists;

    try {
        QSqlQuery query("SELECT id, name, time_interval FROM RandomImageLists");
        if (!query.exec()) {
            throw WSException("Error retrieving all image lists: " + query.lastError().text());
        }

        while (query.next()) {
            int listId = query.value(0).toInt();
            QString name = query.value(1).toString();
            QDateTime timeInterval = query.value(2).toDateTime();
            QVector<int> imageIds = getImageIdsForList(listId);

            RandomImageList randomImageList(name, timeInterval, imageIds);
            randomImageList.setId(listId);
            randomImageLists.append(randomImageList);
        }
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return randomImageLists;
}

// Find a random image list by ID
RandomImageList RandomListTableManager::findListById(int id) {
    try {
        QSqlQuery query;
        query.prepare("SELECT id, name, time_interval FROM RandomImageLists WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSException("Error retrieving list: " + query.lastError().text());
        }

        if (query.next()) {
            int listId = query.value(0).toInt();        // ID of the list
            QString name = query.value(1).toString();   // Name of the list
            QDateTime timeInterval = query.value(2).toDateTime(); // Time interval

            // Get the image IDs associated with the list
            QVector<int> imageIds = getImageIdsForList(listId);

            // Create and return the RandomImageList object
            RandomImageList randomImageList(name, timeInterval, imageIds);
            randomImageList.setId(listId); // Set the list ID
            return randomImageList;
        }
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return RandomImageList(); // Return a default-constructed RandomImageList if not found
}

// Update an existing random image list
bool RandomListTableManager::updateList(const RandomImageList& randomImageList) {
    try {
        if (randomImageList.getId() == -1) {
            throw WSException("Unknown id for random image list!");
        }

        QSqlQuery query;
        query.prepare("UPDATE RandomImageLists SET name = :name, time_interval = :time WHERE id = :id");
        query.bindValue(":name", randomImageList.getName());
        query.bindValue(":time", randomImageList.getTimeInterval());
        query.bindValue(":id", randomImageList.getId());

        if (!query.exec()) {
            throw WSException("Error updating list: " + query.lastError().text());
        }

        // Remove old images
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM RandomImages WHERE random_list_id = :listId");
        deleteQuery.bindValue(":listId", randomImageList.getId());

        if (!deleteQuery.exec()) {
            throw WSException("Error deleting images: " + deleteQuery.lastError().text());
        }

        // Insert new images
        for (int imageId : randomImageList.getImageIds()) {
            QSqlQuery imageQuery;
            imageQuery.prepare("INSERT INTO RandomImages (random_list_id, image_id) VALUES (:listId, :imageId)");
            imageQuery.bindValue(":listId", randomImageList.getId());
            imageQuery.bindValue(":imageId", imageId);

            if (!imageQuery.exec()) {
                throw WSException("Error inserting image: " + imageQuery.lastError().text());
            }
        }

        return true;
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

// Get image IDs for a specific list
QVector<int> RandomListTableManager::getImageIdsForList(int listId) const {
    QVector<int> imageIds;
    QSqlQuery query;
    query.prepare("SELECT image_id FROM RandomImages WHERE random_list_id = :listId");
    query.bindValue(":listId", listId);

    if (query.exec()) {
        while (query.next()) {
            imageIds.append(query.value(0).toInt());
        }
    } else {
        qDebug() << "Error retrieving image ids: " << query.lastError().text();
    }
    return imageIds;
}
