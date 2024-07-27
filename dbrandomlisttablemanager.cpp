#include "dbrandomlisttablemanager.h"

DBRandomListTableManager::DBRandomListTableManager()
{

}
bool DBRandomListTableManager::insertImageList(RandomImageList* imageList) {
    try {
        if (!imageList) {
            throw WSExeptions("Null pointer received for image list!");
        }

        // Serialize the list to JSON format
        QString jsonString = imageList->toJsonString();

        // Insert it into the table
        QSqlQuery query;
        query.prepare("INSERT INTO RandomImageLists (name, time_interval, image_array) VALUES (:name, :time, :images)");
        query.bindValue(":name", imageList->getName());
        query.bindValue(":time", imageList->getTimeInterval());
        query.bindValue(":images", jsonString);

        if (!query.exec()) {
            throw WSExeptions("Error inserting image list into RandomImageLists: " + query.lastError().text());
        }

        // Get the last inserted ID and set it in the non-const object
        imageList->setId(query.lastInsertId().toInt());
        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

QVector<RandomImageList> DBRandomListTableManager::getAllRandomImageLists() {
    QVector<RandomImageList> randomImageLists;

    try {
        QSqlQuery query;
        if (!query.exec("SELECT id, name, time_interval, image_array FROM RandomImageLists")) {
            throw WSExeptions("Error retrieving all random image lists: " + query.lastError().text());
        }

        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QDateTime timeInterval = query.value(2).toDateTime();
            QString jsonImages = query.value(3).toString();

            RandomImageList randomImageList;
            randomImageList.fromJsonString(jsonImages);
            randomImageList.setId(id);
            randomImageList.setName(name);
            randomImageList.setTimeInterval(timeInterval);
            randomImageLists.append(randomImageList);
        }
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return randomImageLists;
}

RandomImageList DBRandomListTableManager::FindRandomImageListById(int id) {
    try {
        QSqlQuery query;
        query.prepare("SELECT id, name, time_interval, image_array FROM RandomImageLists WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSExeptions("Error retrieving random image list: " + query.lastError().text());
        }

        if (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QDateTime timeInterval = query.value(2).toDateTime();
            QString jsonImages = query.value(3).toString();

            RandomImageList randomImageList;
            randomImageList.fromJsonString(jsonImages);
            randomImageList.setId(id);
            randomImageList.setName(name);
            randomImageList.setTimeInterval(timeInterval);
            return randomImageList;
        }
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return RandomImageList(); // Return a default-constructed RandomImageList if no record with such id is found
}

bool DBRandomListTableManager::updateRandomImageList(RandomImageList* randomImageList) {
    try {
        if (!randomImageList) {
            throw WSExeptions("Null pointer received for random image list!");
        }

        // Check if the list's ID is known
        if (randomImageList->getId() == -1) {
            throw WSExeptions("Unknown id for random image list!");
        }

        // Serialize the list to JSON format
        QString jsonString = randomImageList->toJsonString();

        // Update the record in the database
        QSqlQuery query;
        query.prepare("UPDATE RandomImageLists SET name = :name, time_interval = :time, image_array = :images WHERE id = :id");
        query.bindValue(":name", randomImageList->getName());
        query.bindValue(":time", randomImageList->getTimeInterval());
        query.bindValue(":images", jsonString);
        query.bindValue(":id", randomImageList->getId());

        if (!query.exec()) {
            throw WSExeptions("Error updating random image list: " + query.lastError().text());
        }

        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}
