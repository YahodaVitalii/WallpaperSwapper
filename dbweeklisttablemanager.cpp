#include "dbweeklisttablemanager.h"
bool DBWeekListTableManager::insertWeekImageList(WeekImageList* weekImageList) {
    try {
        if (!weekImageList) {
            throw WSExeptions("Null pointer received for week image list!");
        }

        // Вставка у таблицю WeekImagesList
        QSqlQuery query;
        query.prepare("INSERT INTO WeekImageList (name) VALUES (:name)");
        query.bindValue(":name", weekImageList->getName());

        if (!query.exec()) {
            throw WSExeptions("Error inserting week image list into WeekImagesList: " + query.lastError().text());
        }

        int listId = query.lastInsertId().toInt();
        weekImageList->setId(listId);

        // Вставка у таблицю WeekImages
        query.prepare("INSERT INTO WeekImages (list_id, monday, tuesday, wednesday, thursday, friday, saturday, sunday, other_days) "
                      "VALUES (:list_id, :monday, :tuesday, :wednesday, :thursday, :friday, :saturday, :sunday, :other_days)");
        query.bindValue(":list_id", listId);
        query.bindValue(":monday", weekImageList->getImages()["Monday"]);
        query.bindValue(":tuesday", weekImageList->getImages()["Tuesday"]);
        query.bindValue(":wednesday", weekImageList->getImages()["Wednesday"]);
        query.bindValue(":thursday", weekImageList->getImages()["Thursday"]);
        query.bindValue(":friday", weekImageList->getImages()["Friday"]);
        query.bindValue(":saturday", weekImageList->getImages()["Saturday"]);
        query.bindValue(":sunday", weekImageList->getImages()["Sunday"]);
        query.bindValue(":other_days", weekImageList->getImages()["Other days"]);
        if (!query.exec()) {
            throw WSExeptions("Error inserting week images into WeekImages: " + query.lastError().text());
        }

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
        if (!query.exec("SELECT id, name FROM WeekImageList")) {
            throw WSExeptions("Error retrieving all week image lists: " + query.lastError().text());
        }

        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();

            WeekImageList weekImageList;
            weekImageList.setId(id);
            weekImageList.setName(name);

            QSqlQuery imageQuery;
            imageQuery.prepare("SELECT monday, tuesday, wednesday, thursday, friday, saturday, sunday, other_days FROM WeekImages WHERE list_id = :list_id");
            imageQuery.bindValue(":list_id", id);

            if (!imageQuery.exec()) {
                throw WSExeptions("Error retrieving week images for list: " + imageQuery.lastError().text());
            }

            QMap<QString, int> images;
            if (imageQuery.next()) {
                images["Monday"] = imageQuery.value(0).toInt();
                images["Tuesday"] = imageQuery.value(1).toInt();
                images["Wednesday"] = imageQuery.value(2).toInt();
                images["Thursday"] = imageQuery.value(3).toInt();
                images["Friday"] = imageQuery.value(4).toInt();
                images["Saturday"] = imageQuery.value(5).toInt();
                images["Sunday"] = imageQuery.value(6).toInt();
                images["Other days"] = imageQuery.value(7).toInt();
            }

            weekImageList.setImages(images);
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
        query.prepare("SELECT id, name FROM WeekImageList WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSExeptions("Error retrieving week image list: " + query.lastError().text());
        }

        if (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();

            WeekImageList weekImageList;
            weekImageList.setId(id);
            weekImageList.setName(name);

            QSqlQuery imageQuery;
            imageQuery.prepare("SELECT monday, tuesday, wednesday, thursday, friday, saturday, sunday, other_days FROM WeekImages WHERE list_id = :list_id");
            imageQuery.bindValue(":list_id", id);

            if (!imageQuery.exec()) {
                throw WSExeptions("Error retrieving week images for list: " + imageQuery.lastError().text());
            }

            QMap<QString, int> images;
            if (imageQuery.next()) {
                images["Monday"] = imageQuery.value(0).toInt();
                images["Tuesday"] = imageQuery.value(1).toInt();
                images["Wednesday"] = imageQuery.value(2).toInt();
                images["Thursday"] = imageQuery.value(3).toInt();
                images["Friday"] = imageQuery.value(4).toInt();
                images["Saturday"] = imageQuery.value(5).toInt();
                images["Sunday"] = imageQuery.value(6).toInt();
                images["Other days"] = imageQuery.value(7).toInt();
            }

            weekImageList.setImages(images);
            return weekImageList;
        }
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return WeekImageList(); // Повернення пустого об'єкта, якщо нічого не знайдено
}

bool DBWeekListTableManager::updateWeekImageList(WeekImageList* weekImageList) {
    try {
        if (!weekImageList) {
            throw WSExeptions("Null pointer received for week image list!");
        }

        if (weekImageList->getId() == -1) {
            throw WSExeptions("Unknown id for week image list!");
        }

        QSqlQuery query;
        query.prepare("UPDATE WeekImageList SET name = :name WHERE id = :id");
        query.bindValue(":name", weekImageList->getName());
        query.bindValue(":id", weekImageList->getId());

        if (!query.exec()) {
            throw WSExeptions("Error updating week image list: " + query.lastError().text());
        }

        // Оновлення зображень у таблиці WeekImages
        query.prepare("UPDATE WeekImages SET monday = :monday, tuesday = :tuesday, wednesday = :wednesday, thursday = :thursday, "
                      "friday = :friday, saturday = :saturday, sunday = :sunday, other_days = :other_days WHERE list_id = :list_id");
        query.bindValue(":monday", weekImageList->getImages()["Monday"]);
        query.bindValue(":tuesday", weekImageList->getImages()["Tuesday"]);
        query.bindValue(":wednesday", weekImageList->getImages()["Wednesday"]);
        query.bindValue(":thursday", weekImageList->getImages()["Thursday"]);
        query.bindValue(":friday", weekImageList->getImages()["Friday"]);
        query.bindValue(":saturday", weekImageList->getImages()["Saturday"]);
        query.bindValue(":sunday", weekImageList->getImages()["Sunday"]);
        query.bindValue(":other_days", weekImageList->getImages()["Other days"]);
        query.bindValue(":list_id", weekImageList->getId());

        if (!query.exec()) {
            throw WSExeptions("Error updating week images: " + query.lastError().text());
        }

        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}
