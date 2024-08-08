#include "sqlitedbmanager.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOST_NAME);
    db.setDatabaseName(DATABASE_FILE_NAME);
}

// Метод для отримання екземпляру даного класу (патерн Singleton)
SqliteDBManager* SqliteDBManager::getInstance() {
    if (instance == nullptr) {
        instance = new SqliteDBManager();
    }
    return instance;
}


void SqliteDBManager::connectToDataBase() {
    if (QFile(DATABASE_FILE_NAME).exists()) {
        this->openDataBase();

    } else {
        this->restoreDataBase();

    }

}

// Метод для отримання обробника підключення до БД
QSqlDatabase SqliteDBManager::getDB() {
    return db;
}

// Метод відновлення бази даних
bool SqliteDBManager::restoreDataBase() {
    if (!this->openDataBase()) {
        qDebug() << "Не вдалось відкрити базу даних";
        return false;
    }

    qDebug() << "Базу даних відкрито успішно";

    if (!tableCreator.BuildTables()) {
        qDebug() << "Не вдалось створити таблиці";
        return false;
    } else {
        qDebug() << "Таблиці створено успішно";
        return true;
    }
}

bool SqliteDBManager::openDataBase() {

    /* База даних відкривається по вказаному шляху
     * та імені бази даних, якщо вона існує
     * */
    if (db.open()) {

        return true;
    } else
        return false;

}

// Метод закриття бази даних
void SqliteDBManager::closeDataBase() {
    db.close();
}

bool SqliteDBManager::insertIntoImageTable(const WallpaperImage& wallpaperImage) {
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_IMAGE " ("
                  TABLE_IMAGE_NAME ", "
                  TABLE_IMAGE_URL ", "
                  TABLE_IMAGE_HEIGHT ", "
                  TABLE_IMAGE_WIDTH ") "
                                    "VALUES (:Name, :Url, :Height, :Width)");

    query.bindValue(":Name", wallpaperImage.getName());
    query.bindValue(":Url", wallpaperImage.getUrl());
    query.bindValue(":Height", wallpaperImage.getHeight());
    query.bindValue(":Width", wallpaperImage.getWidth());

    if (!query.exec()) {
        qDebug() << "error insert into " << TABLE_IMAGE;
        qDebug() << query.lastError().text();
        return false;
    } else
        return true;
}

QVector<WallpaperImage> SqliteDBManager::getAllImages() {
    QVector<WallpaperImage> images;

    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Failed to open database:" << db.lastError().text();
            return images;
        }
    }

    QSqlQuery query(db);
    QString queryString = QString("SELECT %1, %2, %3, %4, %5 FROM %6")
            .arg(TABLE_IMAGE_ID)
            .arg(TABLE_IMAGE_NAME)
            .arg(TABLE_IMAGE_URL)
            .arg(TABLE_IMAGE_HEIGHT)
            .arg(TABLE_IMAGE_WIDTH)
            .arg(TABLE_IMAGE);

    query.prepare(queryString);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
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
bool SqliteDBManager::deleteImageById(int imageId) {
    if (!db.isOpen() && !db.open()) {
        qDebug() << "Database is not open:" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM Images WHERE id = :id");
    query.bindValue(":id", imageId);

    if (!query.exec()) {
        qDebug() << "Error deleting image from database:" << query.lastError().text();
        return false;
    }

    return true;
}


