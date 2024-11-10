#include "imagetablemanager.h"
bool ImageTableManager::insertIntoTable(const WallpaperImage& wallpaperImage) {
    if (!checkDatabaseConnection()) {
        qDebug() << "Database connection is not available.";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO Images (name, url, height, width) VALUES (:Name, :Url, :Height, :Width)");
    query.bindValue(":Name", wallpaperImage.getName());
    query.bindValue(":Url", wallpaperImage.getUrl());
    query.bindValue(":Height", wallpaperImage.getHeight());
    query.bindValue(":Width", wallpaperImage.getWidth());

    return executeQuery(query);
}

QVector<WallpaperImage> ImageTableManager::getAllRecords() {
    QVector<WallpaperImage> images;

    if (!checkDatabaseConnection()) {
        qDebug() << "Database connection is not available.";
        return images;
    }

    QSqlQuery query("SELECT id, name, url, height, width FROM Images");

    if (!query.exec()) {
        qWarning() << "Error executing query:" << query.lastError().text();
        return images;
    }

    while (query.next()) {
        WallpaperImage image;
        image.setId(query.value(0).toInt());
        image.setName(query.value(1).toString());
        image.setUrl(query.value(2).toString());
        image.setHeight(query.value(3).toInt());
        image.setWidth(query.value(4).toInt());
        images.append(image);
    }

    return images;
}

bool ImageTableManager::deleteImageById(int imageId) {
    if (!checkDatabaseConnection()) {
        qDebug() << "Database connection is not available.";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM Images WHERE id = :id");
    query.bindValue(":id", imageId);

    return executeQuery(query);
}

