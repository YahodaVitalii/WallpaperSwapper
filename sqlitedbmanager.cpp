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
    if (!query.exec("CREATE TABLE List_images_table ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "time_interval TIMESTAMP,"
                       "image_id_1 INTEGER,"
                       "image_id_2 INTEGER,"
                       "image_id_3 INTEGER,"
                       "image_id_4 INTEGER,"
                       "image_id_5 INTEGER,"
                       "image_id_6 INTEGER,"
                       "image_id_7 INTEGER,"
                       "image_id_8 INTEGER,"
                       "image_id_9 INTEGER,"
                       "image_id_10 INTEGER,"
                       "image_id_11 INTEGER,"
                       "image_id_12 INTEGER,"
                       "image_id_13 INTEGER,"
                       "image_id_14 INTEGER,"
                       "image_id_15 INTEGER,"
                       "image_id_16 INTEGER,"
                       "image_id_17 INTEGER,"
                       "image_id_18 INTEGER,"
                       "image_id_19 INTEGER,"
                       "image_id_20 INTEGER,"
                       "FOREIGN KEY (image_id_1) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_2) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_3) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_4) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_5) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_6) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_7) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_8) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_9) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_10) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_11) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_12) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_13) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_14) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_15) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_16) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_17) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_18) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_19) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (image_id_20) REFERENCES TABLE_IMAGE(id))")) {
           qDebug() << "DataBase: error of create images_table";
           qDebug() << query.lastError().text();
           return false;
       }
    if (!query.exec("CREATE TABLE Week_images_table ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "Monday_image_id INTEGER,"
                        "Tuesday_image_id INTEGER,"
                        "Wednesday_image_id INTEGER,"
                        "Thursday_image_id INTEGER,"
                        "Friday_image_id INTEGER,"
                        "Saturday_image_id INTEGER,"
                        "Sunday_image_id INTEGER,"
                        "FOREIGN KEY (Monday_image_id) REFERENCES TABLE_IMAGE(id),"
                        "FOREIGN KEY (Tuesday_image_id) REFERENCES TABLE_IMAGE(id),"
                        "FOREIGN KEY (Wednesday_image_id) REFERENCES TABLE_IMAGE(id),"
                        "FOREIGN KEY (Thursday_image_id) REFERENCES TABLE_IMAGE(id),"
                        "FOREIGN KEY (Friday_image_id) REFERENCES TABLE_IMAGE(id),"
                        "FOREIGN KEY (Saturday_image_id) REFERENCES TABLE_IMAGE(id),"
                        "FOREIGN KEY (Sunday_image_id) REFERENCES TABLE_IMAGE(id))")) {
            qDebug() << "DataBase: error of create images_table";
            qDebug() << query.lastError().text();
            return false;
        }
    if (!query.exec("CREATE TABLE Day_images_table ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                       "hour_00_image_id INTEGER,"
                       "hour_01_image_id INTEGER,"
                       "hour_02_image_id INTEGER,"
                       "hour_03_image_id INTEGER,"
                       "hour_04_image_id INTEGER,"
                       "hour_05_image_id INTEGER,"
                       "hour_06_image_id INTEGER,"
                       "hour_07_image_id INTEGER,"
                       "hour_08_image_id INTEGER,"
                       "hour_09_image_id INTEGER,"
                       "hour_10_image_id INTEGER,"
                       "hour_11_image_id INTEGER,"
                       "hour_12_image_id INTEGER,"
                       "hour_13_image_id INTEGER,"
                       "hour_14_image_id INTEGER,"
                       "hour_15_image_id INTEGER,"
                       "hour_16_image_id INTEGER,"
                       "hour_17_image_id INTEGER,"
                       "hour_18_image_id INTEGER,"
                       "hour_19_image_id INTEGER,"
                       "hour_20_image_id INTEGER,"
                       "hour_21_image_id INTEGER,"
                       "hour_22_image_id INTEGER,"
                       "hour_23_image_id INTEGER,"
                       "FOREIGN KEY (hour_00_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_01_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_02_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_03_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_04_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_05_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_06_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_07_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_08_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_09_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_10_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_11_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_12_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_13_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_14_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_15_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_16_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_17_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_18_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_19_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_20_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_21_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_22_image_id) REFERENCES TABLE_IMAGE(id),"
                       "FOREIGN KEY (hour_23_image_id) REFERENCES TABLE_IMAGE(id))")) {
           qDebug() << "DataBase: error of create imagessss";
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
        WlapperImage image;
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



