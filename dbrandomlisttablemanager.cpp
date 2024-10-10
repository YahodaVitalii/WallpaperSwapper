#include "dbrandomlisttablemanager.h"

bool DBRandomListTableManager::insertImageList(RandomImageList* imageList) {
    try {
        if (!imageList) {
            throw WSExceptions("Null pointer received for image list!");
        }

        QSqlQuery query;
        query.prepare("INSERT INTO RandomImageLists (name, time_interval) VALUES (:name, :time)");
        query.bindValue(":name", imageList->getName());
        query.bindValue(":time", imageList->getTimeInterval());

        if (!query.exec()) {
            throw WSExceptions("Error inserting image list into RandomImageLists: " + query.lastError().text());
        }

        int listId = query.lastInsertId().toInt();
        imageList->setId(listId);

        // Вставка зображень у таблицю RandomImages
        for (int imageId : imageList->getImageIds()) {
            QSqlQuery imageQuery;
            imageQuery.prepare("INSERT INTO RandomImages (random_list_id, image_id) VALUES (:listId, :imageId)");
            imageQuery.bindValue(":listId", listId);
            imageQuery.bindValue(":imageId", imageId);

            if (!imageQuery.exec()) {
                throw WSExceptions("Error inserting image into RandomImages: " + imageQuery.lastError().text());
            }
        }
        return true;
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

QVector<RandomImageList> DBRandomListTableManager::getAllRandomImageLists() {
    QVector<RandomImageList> randomImageLists;

    try {
        QSqlQuery query;
        if (!query.exec("SELECT id, name, time_interval FROM RandomImageLists")) {
            throw WSExceptions("Error retrieving all random image lists: " + query.lastError().text());
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
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return randomImageLists;
}

RandomImageList DBRandomListTableManager::FindRandomImageListById(int id) {
    try {
        QSqlQuery query;
        query.prepare("SELECT id, name, time_interval FROM RandomImageLists WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSExceptions("Error retrieving random image list: " + query.lastError().text());
        }

        if (query.next()) {
            QString name = query.value(1).toString();
            QDateTime timeInterval = query.value(2).toDateTime();

            QVector<int> imageIds = getImageIdsForList(id);

            RandomImageList randomImageList(name, timeInterval, imageIds);
            randomImageList.setId(id);
            return randomImageList;
        }
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return RandomImageList(); // Return a default-constructed RandomImageList if no record with such id is found
}

bool DBRandomListTableManager::updateRandomImageList(RandomImageList* randomImageList) {
    try {
        if (!randomImageList) {
            throw WSExceptions("Null pointer received for random image list!");
        }

        if (randomImageList->getId() == -1) {
            throw WSExceptions("Unknown id for random image list!");
        }

        QSqlQuery query;
        query.prepare("UPDATE RandomImageLists SET name = :name, time_interval = :time WHERE id = :id");
        query.bindValue(":name", randomImageList->getName());
        query.bindValue(":time", randomImageList->getTimeInterval());
        query.bindValue(":id", randomImageList->getId());

        if (!query.exec()) {
            throw WSExceptions("Error updating random image list: " + query.lastError().text());
        }

        // Видалення старих зображень
        QSqlQuery deleteQuery;
        deleteQuery.prepare("DELETE FROM RandomImages WHERE random_list_id = :listId");
        deleteQuery.bindValue(":listId", randomImageList->getId());

        if (!deleteQuery.exec()) {
            throw WSExceptions("Error deleting old images: " + deleteQuery.lastError().text());
        }

        // Додавання нових зображень
        for (int imageId : randomImageList->getImageIds()) {
            QSqlQuery imageQuery;
            imageQuery.prepare("INSERT INTO RandomImages (random_list_id, image_id) VALUES (:listId, :imageId)");
            imageQuery.bindValue(":listId", randomImageList->getId());
            imageQuery.bindValue(":imageId", imageId);

            if (!imageQuery.exec()) {
                throw WSExceptions("Error inserting image into RandomImages: " + imageQuery.lastError().text());
            }
        }

        return true;
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

QVector<int> DBRandomListTableManager::getImageIdsForList(int listId) const {
    QVector<int> imageIds;
    QSqlQuery query;
    query.prepare("SELECT image_id FROM RandomImages WHERE random_list_id = :listId");
    query.bindValue(":listId", listId);

    if (query.exec()) {
        while (query.next()) {
            imageIds.append(query.value(0).toInt());
        }
    } else {
        qDebug() << "Error retrieving image ids for list: " << query.lastError().text();
    }
    return imageIds;
}
