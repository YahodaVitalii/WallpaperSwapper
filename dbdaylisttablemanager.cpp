#include "dbdaylisttablemanager.h"

DBDayListTableManager::DBDayListTableManager()
{

}
bool DBDayListTableManager::insertDayImageList(DayImageList* dayImageList) {
    try {
        if (!dayImageList) {
            throw WSExeptions("Null pointer received for day image list!");
        }

        // Serialize the list to JSON format
        QString jsonString = dayImageList->toJsonString();

        // Insert it into the table
        QSqlQuery query;
        query.prepare("INSERT INTO Day_images_table (name, images) VALUES (:name, :images)");
        query.bindValue(":name", dayImageList->getName());
        query.bindValue(":images", jsonString);

        if (!query.exec()) {
            throw WSExeptions("Error inserting day image list into Day_images_table: " + query.lastError().text());
        }

        // Get the last inserted ID and set it in the non-const object
        dayImageList->setId(query.lastInsertId().toInt());

        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

QVector<DayImageList> DBDayListTableManager::getAllDayImageLists() {
    QVector<DayImageList> dayImageLists;

    try {
        QSqlQuery query;
        if (!query.exec("SELECT id, name, images FROM Day_images_table")) {
            throw WSExeptions("Error retrieving all day image lists: " + query.lastError().text());
        }

        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString jsonImages = query.value(2).toString();

            DayImageList dayImageList;
            dayImageList.fromJsonString(jsonImages);
            dayImageList.setId(id);
            dayImageList.setName(name); // Set the name
            dayImageLists.append(dayImageList);
        }
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return dayImageLists;
}

DayImageList DBDayListTableManager::findDayImageListById(int id) {
    try {
        QSqlQuery query;
        query.prepare("SELECT id, name, images FROM Day_images_table WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSExeptions("Error retrieving day image list: " + query.lastError().text());
        }

        if (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString jsonImages = query.value(2).toString();

            DayImageList dayImageList;
            dayImageList.fromJsonString(jsonImages);
            dayImageList.setId(id);
            dayImageList.setName(name); // Set the name
            return dayImageList;
        }
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return DayImageList(); // Return a default-constructed DayImageList if no record with such id is found
}

bool DBDayListTableManager::updateDayImageList(DayImageList* dayImageList) {
    try {
        if (!dayImageList) {
            throw WSExeptions("Null pointer received for day image list!");
        }

        // Check if the list's ID is known
        if (dayImageList->getId() == -1) {
            throw WSExeptions("Unknown id for day image list!");
        }

        // Serialize the list to JSON format
        QString jsonString = dayImageList->toJsonString();

        // Update the record in the database
        QSqlQuery query;
        query.prepare("UPDATE Day_images_table SET name = :name, images = :images WHERE id = :id");
        query.bindValue(":name", dayImageList->getName());
        query.bindValue(":images", jsonString);
        query.bindValue(":id", dayImageList->getId());

        if (!query.exec()) {
            throw WSExeptions("Error updating day image list: " + query.lastError().text());
        }

        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}
