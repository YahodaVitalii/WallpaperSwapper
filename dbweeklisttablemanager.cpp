#include "dbweeklisttablemanager.h"

DBWeekListTableManager::DBWeekListTableManager()
{

}
bool DBWeekListTableManager::insertWeekImageList(WeekImageList* weekImageList) {
    try {
        if (!weekImageList) {
            throw WSExeptions("Null pointer received for week image list!");
        }

        // Serialize the list to JSON format
        QString jsonString = weekImageList->toJsonString();

        // Insert it into the table
        QSqlQuery query;
        query.prepare("INSERT INTO Week_images_table (name, images) VALUES (:name, :images)");
        query.bindValue(":name", weekImageList->getName());
        query.bindValue(":images", jsonString);

        if (!query.exec()) {
            throw WSExeptions("Error inserting week image list into Week_images_table: " + query.lastError().text());
        }

        // Get the last inserted ID and set it in the non-const object
        weekImageList->setId(query.lastInsertId().toInt());
        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

QVector<WeekImageList> DBWeekListTableManager::getAllWeekImageLists() {
    QVector<WeekImageList> weekImageLists;

    try {
        QSqlQuery query;
        if (!query.exec("SELECT id, name, images FROM Week_images_table")) {
            throw WSExeptions("Error retrieving all week image lists: " + query.lastError().text());
        }

        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString jsonImages = query.value(2).toString();

            WeekImageList weekImageList;
            weekImageList.fromJsonString(jsonImages);
            weekImageList.setId(id);
            weekImageList.setName(name); // Set the name
            weekImageLists.append(weekImageList);
        }
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return weekImageLists;
}

WeekImageList DBWeekListTableManager::findWeekImageListById(int id) {
    try {
        QSqlQuery query;
        query.prepare("SELECT id, name, images FROM Week_images_table WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSExeptions("Error retrieving week image list: " + query.lastError().text());
        }

        if (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString jsonImages = query.value(2).toString();

            WeekImageList weekImageList;
            weekImageList.fromJsonString(jsonImages);
            weekImageList.setId(id);
            weekImageList.setName(name); // Set the name
            return weekImageList;
        }
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return WeekImageList(); // Return a default-constructed WeekImageList if no record with such id is found
}

bool DBWeekListTableManager::updateWeekImageList(WeekImageList* weekImageList) {
    try {
        if (!weekImageList) {
            throw WSExeptions("Null pointer received for week image list!");
        }

        // Check if the list's ID is known
        if (weekImageList->getId() == -1) {
            throw WSExeptions("Unknown id for week image list!");
        }

        // Serialize the list to JSON format
        QString jsonString = weekImageList->toJsonString();

        // Update the record in the database
        QSqlQuery query;
        query.prepare("UPDATE Week_images_table SET name = :name, images = :images WHERE id = :id");
        query.bindValue(":name", weekImageList->getName());
        query.bindValue(":images", jsonString);
        query.bindValue(":id", weekImageList->getId());

        if (!query.exec()) {
            throw WSExeptions("Error updating week image list: " + query.lastError().text());
        }

        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}
