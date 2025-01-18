#include "moodlisttablemeneger.h"

#include "moodlisttablemeneger.h"

MoodListTableMeneger::MoodListTableMeneger() {}

// Insert a new mood image record
bool MoodListTableMeneger::insertIntoTable(const QPair<int, int>& moodImage) {
    QSqlQuery query;
    query.prepare("INSERT INTO MoodImageList (emodjiId, imageId) VALUES (:emodjiId, :imageId)");
    query.bindValue(":emodjiId", moodImage.first);
    query.bindValue(":imageId", moodImage.second);

    if (!query.exec()) {
        throw WSException("Error inserting mood image: " + query.lastError().text());
    }

    return true;
}

// Retrieve all mood images
QMap<int, int> MoodListTableMeneger::getAllRecords() {
    QMap<int, int> moodImageMap;
    QSqlQuery query("SELECT emodjiId, imageId FROM MoodImageList");

    if (!query.exec()) {
        throw WSException("Error retrieving mood images: " + query.lastError().text());
    }

    while (query.next()) {
        int emodjiId = query.value(0).toInt();
        int imageId = query.value(1).toInt();
        moodImageMap.insert(emodjiId, imageId);
    }

    return moodImageMap;
}

// Update an existing mood image
bool MoodListTableMeneger::updateList(const QPair<int, int>& moodImage) {
    QSqlQuery query;
    query.prepare("UPDATE MoodImageList SET imageId = :imageId WHERE emodjiId = :emodjiId");
    query.bindValue(":imageId", moodImage.second);
    query.bindValue(":emodjiId", moodImage.first);

    if (!query.exec()) {
        throw WSException("Error updating mood image: " + query.lastError().text());
    }

    return true;
}

// Find a mood image by emodjiId
QPair<int, int> MoodListTableMeneger::findListById(int emodjiId) {
    QSqlQuery query;
    query.prepare("SELECT imageId, anotherColumn FROM MoodImageList WHERE emodjiId = :emodjiId");
    query.bindValue(":emodjiId", emodjiId);

    if (!query.exec()) {
        throw WSException("Error finding image by emodjiId: " + query.lastError().text());
    }

    if (query.next()) {
        int imageId = query.value(0).toInt();
        int anotherValue = query.value(1).toInt();  // Replace with the second column you need
        return QPair<int, int>(imageId, anotherValue);
    }

    return QPair<int, int>(-1, -1); // Return an invalid pair if not found
}

// Delete a mood image by emodjiId and imageId
bool MoodListTableMeneger::deleteMoodImage(int emodjiId, int imageId) {
    QSqlQuery query;
    query.prepare("DELETE FROM MoodImageList WHERE emodjiId = :emodjiId AND imageId = :imageId");
    query.bindValue(":emodjiId", emodjiId);
    query.bindValue(":imageId", imageId);

    if (!query.exec()) {
        throw WSException("Error deleting mood image: " + query.lastError().text());
    }

    return true;
}

