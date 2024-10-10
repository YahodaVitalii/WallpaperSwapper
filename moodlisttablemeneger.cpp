#include "moodlisttablemeneger.h"

MoodListTableMeneger::MoodListTableMeneger()
{
}

// Функція для вставки нового запису у MoodImageList
bool MoodListTableMeneger::insertMoodImage(int emodjiId, int imageId) {
    try {
        if (emodjiId == -1 || imageId == -1) {
            throw WSExceptions("Invalid emodjiId or imageId provided!");
        }

        QSqlQuery query;
        query.prepare("INSERT INTO MoodImageList (emodjiId, imageId) VALUES (:emodjiId, :imageId)");
        query.bindValue(":emodjiId", emodjiId);
        query.bindValue(":imageId", imageId);

        if (!query.exec()) {
            throw WSExceptions("Error inserting mood image into MoodImageList: " + query.lastError().text());
        }

        return true;
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

// Функція для отримання всіх записів MoodImageList
QMap<int, int> MoodListTableMeneger::getAllMoodImages() {
    QMap<int, int> moodImageMap;

    try {
        QSqlQuery query;
        if (!query.exec("SELECT emodjiId, imageId FROM MoodImageList")) {
            throw WSExceptions("Error retrieving all mood images: " + query.lastError().text());
        }

        while (query.next()) {
            int emodjiId = query.value(0).toInt();
            int imageId = query.value(1).toInt();

            moodImageMap.insert(emodjiId, imageId);  // Вставляємо у QMap
        }
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return moodImageMap;
}

// Функція для отримання imageId за emodjiId
int MoodListTableMeneger::findImageByEmodjiId(int emodjiId) {
    int imageId = -1;  // Значення за замовчуванням, якщо не знайдено

    try {
        QSqlQuery query;
        query.prepare("SELECT imageId FROM MoodImageList WHERE emodjiId = :emodjiId");
        query.bindValue(":emodjiId", emodjiId);

        if (!query.exec()) {
            throw WSExceptions("Error retrieving image for emodji: " + query.lastError().text());
        }

        if (query.next()) {
            imageId = query.value(0).toInt();  // Повертаємо перший знайдений imageId
        }
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
    }

    return imageId;
}

// Функція для оновлення запису
bool MoodListTableMeneger::updateMoodImage(int emodjiId, int newImageId) {
    try {
        if (emodjiId == -1 || newImageId == -1) {
            throw WSExceptions("Invalid emodjiId or imageId provided for update!");
        }

        QSqlQuery query;
        query.prepare("UPDATE MoodImageList SET imageId = :newImageId WHERE emodjiId = :emodjiId");
        query.bindValue(":newImageId", newImageId);
        query.bindValue(":emodjiId", emodjiId);

        if (!query.exec()) {
            throw WSExceptions("Error updating mood image in MoodImageList: " + query.lastError().text());
        }

        return true;
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}

// Функція для видалення запису за emodjiId та imageId
bool MoodListTableMeneger::deleteMoodImage(int emodjiId, int imageId) {
    try {
        QSqlQuery query;
        query.prepare("DELETE FROM MoodImageList WHERE emodjiId = :emodjiId AND imageId = :imageId");
        query.bindValue(":emodjiId", emodjiId);
        query.bindValue(":imageId", imageId);

        if (!query.exec()) {
            throw WSExceptions("Error deleting mood image from MoodImageList: " + query.lastError().text());
        }

        return true;
    } catch (const WSExceptions& ex) {
        qDebug() << "Exception:" << ex.getMessage();
        return false;
    }
}
