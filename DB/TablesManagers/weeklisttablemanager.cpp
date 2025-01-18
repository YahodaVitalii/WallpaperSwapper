#include "weeklisttablemanager.h"

bool WeekListTableManager::insertIntoTable(const WeekImageList& weekImageList) {
    try {
        // Insert the WeekImageList into the database
        QSqlQuery query;
        query.prepare("INSERT INTO WeekImageList (name) VALUES (:name)");
        query.bindValue(":name", weekImageList.getName());

        if (!query.exec()) {
            throw WSException("Error inserting week image list into WeekImageList: " + query.lastError().text());
        }

        int listId = query.lastInsertId().toInt();
        // You would likely need to update the `weekImageList` with the new `id`, if necessary

        // Insert into the WeekImages table
        query.prepare("INSERT INTO WeekImages (list_id, monday, tuesday, wednesday, thursday, friday, saturday, sunday, other_days) "
                      "VALUES (:list_id, :monday, :tuesday, :wednesday, :thursday, :friday, :saturday, :sunday, :other_days)");
        query.bindValue(":list_id", listId);
        query.bindValue(":monday", weekImageList.getImages()[DayOfWeek::Monday]);
        query.bindValue(":tuesday", weekImageList.getImages()[DayOfWeek::Tuesday]);
        query.bindValue(":wednesday", weekImageList.getImages()[DayOfWeek::Wednesday]);
        query.bindValue(":thursday", weekImageList.getImages()[DayOfWeek::Thursday]);
        query.bindValue(":friday", weekImageList.getImages()[DayOfWeek::Friday]);
        query.bindValue(":saturday", weekImageList.getImages()[DayOfWeek::Saturday]);
        query.bindValue(":sunday", weekImageList.getImages()[DayOfWeek::Sunday]);
        query.bindValue(":other_days", weekImageList.getImages()[DayOfWeek::OtherDays]);

        if (!query.exec()) {
            throw WSException("Error inserting week images into WeekImages: " + query.lastError().text());
        }

        return true;
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

QVector<WeekImageList> WeekListTableManager::getAllRecords() {
    QVector<WeekImageList> weekImageLists;
    try {
        QSqlQuery query;
        if (!query.exec("SELECT id, name FROM WeekImageList")) {
            throw WSException("Error retrieving all week image lists: " + query.lastError().text());
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
                throw WSException("Error retrieving week images for list: " + imageQuery.lastError().text());
            }

            QMap<DayOfWeek, int> images;
            if (imageQuery.next()) {
                images[DayOfWeek::Monday] = imageQuery.value(0).toInt();
                images[DayOfWeek::Tuesday] = imageQuery.value(1).toInt();
                images[DayOfWeek::Wednesday] = imageQuery.value(2).toInt();
                images[DayOfWeek::Thursday] = imageQuery.value(3).toInt();
                images[DayOfWeek::Friday] = imageQuery.value(4).toInt();
                images[DayOfWeek::Saturday] = imageQuery.value(5).toInt();
                images[DayOfWeek::Sunday] = imageQuery.value(6).toInt();
                images[DayOfWeek::OtherDays] = imageQuery.value(7).toInt();
            }

            weekImageList.setImages(images);
            weekImageLists.append(weekImageList);
        }
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return weekImageLists;
}

bool WeekListTableManager::updateList(const WeekImageList& weekImageList) {
    try {
        // Updating the week image list and its associated images
        QSqlQuery query;
        query.prepare("UPDATE WeekImageList SET name = :name WHERE id = :id");
        query.bindValue(":name", weekImageList.getName());
        query.bindValue(":id", weekImageList.getId());

        if (!query.exec()) {
            throw WSException("Error updating week image list: " + query.lastError().text());
        }

        query.prepare("UPDATE WeekImages SET monday = :monday, tuesday = :tuesday, wednesday = :wednesday, thursday = :thursday, "
                      "friday = :friday, saturday = :saturday, sunday = :sunday, other_days = :other_days WHERE list_id = :list_id");
        query.bindValue(":monday", weekImageList.getImages()[DayOfWeek::Monday]);
        query.bindValue(":tuesday", weekImageList.getImages()[DayOfWeek::Tuesday]);
        query.bindValue(":wednesday", weekImageList.getImages()[DayOfWeek::Wednesday]);
        query.bindValue(":thursday", weekImageList.getImages()[DayOfWeek::Thursday]);
        query.bindValue(":friday", weekImageList.getImages()[DayOfWeek::Friday]);
        query.bindValue(":saturday", weekImageList.getImages()[DayOfWeek::Saturday]);
        query.bindValue(":sunday", weekImageList.getImages()[DayOfWeek::Sunday]);
        query.bindValue(":other_days", weekImageList.getImages()[DayOfWeek::OtherDays]);
        query.bindValue(":list_id", weekImageList.getId());

        if (!query.exec()) {
            throw WSException("Error updating week images: " + query.lastError().text());
        }

        return true;
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

WeekImageList WeekListTableManager::findListById(int id) {
    try {
        QSqlQuery query;
        query.prepare("SELECT id, name FROM WeekImageList WHERE id = :id");
        query.bindValue(":id", id);

        if (!query.exec()) {
            throw WSException("Error retrieving week image list: " + query.lastError().text());
        }

        if (query.next()) {
            int listId = query.value(0).toInt();
            QString name = query.value(1).toString();

            WeekImageList weekImageList;
            weekImageList.setId(listId);
            weekImageList.setName(name);

            QSqlQuery imageQuery;
            imageQuery.prepare("SELECT monday, tuesday, wednesday, thursday, friday, saturday, sunday, other_days FROM WeekImages WHERE list_id = :list_id");
            imageQuery.bindValue(":list_id", listId);

            if (!imageQuery.exec()) {
                throw WSException("Error retrieving week images for list: " + imageQuery.lastError().text());
            }

            QMap<DayOfWeek, int> images;
            if (imageQuery.next()) {
                images[DayOfWeek::Monday] = imageQuery.value(0).toInt();
                images[DayOfWeek::Tuesday] = imageQuery.value(1).toInt();
                images[DayOfWeek::Wednesday] = imageQuery.value(2).toInt();
                images[DayOfWeek::Thursday] = imageQuery.value(3).toInt();
                images[DayOfWeek::Friday] = imageQuery.value(4).toInt();
                images[DayOfWeek::Saturday] = imageQuery.value(5).toInt();
                images[DayOfWeek::Sunday] = imageQuery.value(6).toInt();
                images[DayOfWeek::OtherDays] = imageQuery.value(7).toInt();
            }

            weekImageList.setImages(images);
            return weekImageList;
        }
    } catch (const WSException& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return WeekImageList(); // Return an empty object if not found
}
