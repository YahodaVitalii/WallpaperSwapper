#include "dbimagetablemanager.h"

DBImageTableManager::DBImageTableManager() {
    // Ensure the database connection is open
//    if (!checkDatabaseConnection()) {
//        qDebug() << "Database connection could not be established in constructor!";
//    }
}

bool DBImageTableManager::checkDatabaseConnection() {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "Database is not open. Attempting to open.";
        if (!db.open()) {
            qDebug() << "Failed to open database:" << db.lastError().text();
            return false;
        }
    }
   // qDebug() << "Database connection is open.";
    return true;
}

bool DBImageTableManager::insertIntoImageTable(const WallpaperImage& wallpaperImage) {
    if (!checkDatabaseConnection()) {
        qDebug() << "Database connection is not available.";
        return false;
    }

    try {
        QSqlQuery query;
        query.prepare("INSERT INTO Images (name, url, height, width) VALUES (:Name, :Url, :Height, :Width)");

        query.bindValue(":Name", wallpaperImage.getName());
        query.bindValue(":Url", wallpaperImage.getUrl());
        query.bindValue(":Height", wallpaperImage.getHeight());
        query.bindValue(":Width", wallpaperImage.getWidth());

        if (!query.exec()) {
            throw WSExeptions("Error inserting into Images: " + query.lastError().text());
        }
        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception in insertIntoImageTable:" << ex.getMessage();
        return false;
    }
}

QVector<WallpaperImage> DBImageTableManager::getAllImages() {
    QVector<WallpaperImage> images;

    if (!checkDatabaseConnection()) {
        qDebug() << "Database connection is not available.";
        return images;
    }

    try {
        QSqlQuery query;
        QString queryString = QString("SELECT id, name, url, height, width FROM Images");

        if (!query.prepare(queryString)) {
            throw WSExeptions("Error preparing query: " + query.lastError().text());
        }
        //qDebug() << "Query prepared:" << queryString;

        if (!query.exec()) {
            throw WSExeptions("Error executing query: " + query.lastError().text());
        }

      //  qDebug() << "Query executed successfully";

        while (query.next()) {
            WallpaperImage image;
            image.setId(query.value(0).toInt());
            image.setName(query.value(1).toString());
            image.setUrl(query.value(2).toString());
            image.setHeight(query.value(3).toInt());
            image.setWidth(query.value(4).toInt());
            images.append(image);
        }

       // qDebug() << "Loaded images count: " << images.size();
        return images;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception in getAllImages:" << ex.getMessage();
        return images;
    }
}

bool DBImageTableManager::deleteImageById(int imageId) {
    if (!checkDatabaseConnection()) {
        qDebug() << "Database connection is not available.";
        return false;
    }

    try {
        QSqlQuery query;
        query.prepare("DELETE FROM Images WHERE id = :id");
        query.bindValue(":id", imageId);

        if (!query.exec()) {
            throw WSExeptions("Error deleting image from database: " + query.lastError().text());
        }

        return true;
    } catch (const WSExeptions& ex) {
        qDebug() << "Exception in deleteImageById:" << ex.getMessage();
        return false;
    }
}
