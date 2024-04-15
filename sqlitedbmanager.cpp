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

    if (!this->createTables()) {
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

// Метод для створення таблиці в базі даних
bool SqliteDBManager::createTables() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE " TABLE_IMAGE " ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    TABLE_IMAGE_NAME " VARCHAR(255) NOT NULL, "
                    TABLE_IMAGE_URL " TEXT NOT NULL, "
                    TABLE_IMAGE_HEIGHT " INTEGER NOT NULL, "
                    TABLE_IMAGE_WIDTH " INTEGER NOT NULL"
                    " )"
                    )) {
        qDebug() << "DataBase: error of create " << TABLE_IMAGE;
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}


bool SqliteDBManager::insertIntoImageTable(const WlapperImage& wlapperImage) {
    QSqlQuery query;
    query.prepare("INSERT INTO " TABLE_IMAGE " ("
                  TABLE_IMAGE_NAME ", "
                  TABLE_IMAGE_URL ", "
                  TABLE_IMAGE_HEIGHT ", "
                  TABLE_IMAGE_WIDTH ") "
                  "VALUES (:Name, :Url, :Height, :Width)");

    query.bindValue(":Name", wlapperImage.getName());
    query.bindValue(":Url", wlapperImage.getUrl());
    query.bindValue(":Height", wlapperImage.getHeight());
    query.bindValue(":Width", wlapperImage.getWidth());

    if (!query.exec()) {
        qDebug() << "error insert into " << TABLE_IMAGE;
        qDebug() << query.lastError().text();
        return false;
    } else
        return true;
}

QVector<WlapperImage> SqliteDBManager::getAllImages() {
    QVector<WlapperImage> images;

    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Failed to open database:" << db.lastError().text();
            return images;
        }
    }

    QSqlQuery query(db);
    QString queryString = QString("SELECT %1, %2, %3, %4 FROM %5")
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
        WlapperImage image;
        image.setName(query.value(0).toString());
        image.setUrl(query.value(1).toString());
        image.setHeight(query.value(2).toInt());
        image.setWidth(query.value(3).toInt());
        images.append(image);
    }

    return images;
}




