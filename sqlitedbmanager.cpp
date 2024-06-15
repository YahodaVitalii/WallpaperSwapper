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
    if (!query.exec("CREATE TABLE RandomImageLists ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name VARCHAR(255) NOT NULL,"
                    "time_interval TIMESTAMP NOT NULL, "
                    "image_array TEXT NOT NULL)"
                    )) {
        qDebug() << "DataBase: error creating RandomImageLists";
        qDebug() << query.lastError().text();
        return false;
    }
    if (!query.exec("CREATE TABLE Week_images_table ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT,"
                    "images TEXT)")) {
        qDebug() << "DataBase: error of create images_table";
        qDebug() << query.lastError().text();
        return false;
    }
    if (!query.exec("CREATE TABLE Day_images_table ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT, "
                    "images TEXT)")) {
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

bool SqliteDBManager::insertImageList( RandomImageList *imageList){
    if (!imageList) {
        qDebug() << "Null pointer received for image list!";
        return false;
    }
    // Серіалізуємо список у формат JSON
    QString jsonString = imageList->toJsonString();
    // Записуємо його в таблицю
    QSqlQuery query;
    query.prepare("INSERT INTO RandomImageLists (name, time_interval, image_array) VALUES (:name, :time, :images)");
     query.bindValue(":name", imageList->getName());
    query.bindValue(":time", imageList->getTimeInterval());
    query.bindValue(":images", jsonString);

    if (!query.exec()) {
        qDebug() << "Error inserting image list into RandomImageLists:" << query.lastError().text();
        return false;
    }
    // Отримуємо останній доданий ID та встановлюємо його у не `const` об'єкті
    imageList->setId(query.lastInsertId().toInt());

    return true;
}

QVector<RandomImageList> SqliteDBManager::getAllRandomImageLists(){
    QVector<RandomImageList> randomImageLists;

    QSqlQuery query;
    if (!query.exec("SELECT id, name, time_interval, image_array FROM RandomImageLists")) {
        qDebug() << "Error retrieving all random image lists:" << query.lastError().text();
        return randomImageLists; // Return an empty array in case of error
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QDateTime timeInterval = query.value(2).toDateTime();
        QString jsonImages = query.value(3).toString();

        RandomImageList randomImageList;
        randomImageList.fromJsonString(jsonImages);
        randomImageList.setId(id);
        randomImageList.setName(name); // Set the name
        randomImageList.setTimeInterval(timeInterval); // Set the time interval
        randomImageLists.append(randomImageList);
    }

    return randomImageLists;
}

RandomImageList SqliteDBManager::FindRandomImageListById(int id) {
    QSqlQuery query;
    query.prepare("SELECT id, name, time_interval, image_array FROM RandomImageLists WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error retrieving random image list:" << query.lastError().text();
        return RandomImageList(); // Return a default-constructed RandomImageList in case of error
    }

    if (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QDateTime timeInterval = query.value(2).toDateTime();
        QString jsonImages = query.value(3).toString();

        RandomImageList randomImageList;
        randomImageList.fromJsonString(jsonImages);
        randomImageList.setId(id);
        randomImageList.setName(name); // Set the name
        randomImageList.setTimeInterval(timeInterval); // Set the time interval
     //qDebug()<<randomImageList.getImageIds().size();
        return randomImageList;
    }

    return RandomImageList(); // Return a default-constructed RandomImageList if no record with such id is found
}
bool SqliteDBManager::updateRandomImageList(RandomImageList* randomImageList) {
    if (!randomImageList) {
        qDebug() << "Null pointer received for random image list!";
        return false;
    }

    // Перевірка, чи відомий ідентифікатор списку
    if (randomImageList->getId() == -1) {
        qDebug() << "Unknown id for random image list!";
        return false;
    }

    // Серіалізація списку у формат JSON
    QString jsonString = randomImageList->toJsonString();

    // Оновлення запису в базі даних
    QSqlQuery query;
    query.prepare("UPDATE RandomImageLists SET name = :name, time_interval = :time, image_array = :images WHERE id = :id");
    query.bindValue(":name", randomImageList->getName());
    query.bindValue(":time", randomImageList->getTimeInterval());
    query.bindValue(":images", jsonString);
    query.bindValue(":id", randomImageList->getId());

    if (!query.exec()) {
        qDebug() << "Error updating random image list:" << query.lastError().text();
        return false;
    }

    return true;
}
bool SqliteDBManager::insertWeekImageList(WeekImageList* weekImageList){
    if (!weekImageList) {
        qDebug() << "Null pointer received for week image list!";
        return false;
    }
    // Серіалізуємо список у формат JSON
    QString jsonString = weekImageList->toJsonString();
    // Записуємо його в таблицю
    QSqlQuery query;
    query.prepare("INSERT INTO Week_images_table (name, images) VALUES (:name, :images)");
    query.bindValue(":name", weekImageList->getName());
    query.bindValue(":images", jsonString);

    if (!query.exec()) {
        qDebug() << "Error inserting week image list into Week_images_table:" << query.lastError().text();
        return false;
    }
    // Отримуємо останній доданий ID та встановлюємо його у не `const` об'єкті
    weekImageList->setId(query.lastInsertId().toInt());

    return true;
}

QVector<WeekImageList> SqliteDBManager::getAllWeekImageLists(){
    QVector<WeekImageList> weekImageLists;

    QSqlQuery query;
    if (!query.exec("SELECT id, name, images FROM Week_images_table")) {
        qDebug() << "Error retrieving all week image lists:" << query.lastError().text();
        return weekImageLists; // Return an empty array in case of error
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

    return weekImageLists;
}

WeekImageList SqliteDBManager::findWeekImageListById(int id) {
    QSqlQuery query;
    query.prepare("SELECT id, name, images FROM Week_images_table WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error retrieving week image list:" << query.lastError().text();
        return WeekImageList(); // Return a default-constructed WeekImageList in case of error
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

    return WeekImageList(); // Return a default-constructed WeekImageList if no record with such id is found
}

bool SqliteDBManager::updateWeekImageList(WeekImageList* weekImageList) {
    if (!weekImageList) {
        qDebug() << "Null pointer received for week image list!";
        return false;
    }

    // Перевірка, чи відомий ідентифікатор списку
    if (weekImageList->getId() == -1) {
        qDebug() << "Unknown id for week image list!";
        return false;
    }

    // Серіалізація списку у формат JSON
    QString jsonString = weekImageList->toJsonString();

    // Оновлення запису в базі даних
    QSqlQuery query;
    query.prepare("UPDATE Week_images_table SET name = :name, images = :images WHERE id = :id");
    query.bindValue(":name", weekImageList->getName());
    query.bindValue(":images", jsonString);
    query.bindValue(":id", weekImageList->getId());

    if (!query.exec()) {
        qDebug() << "Error updating week image list:" << query.lastError().text();
        return false;
    }

    return true;
}
bool SqliteDBManager::insertDayImageList(DayImageList* dayImageList){
    if (!dayImageList) {
        qDebug() << "Null pointer received for day image list!";
        return false;
    }
    // Серіалізуємо список у формат JSON
    QString jsonString = dayImageList->toJsonString();
    // Записуємо його в таблицю
    QSqlQuery query;
    query.prepare("INSERT INTO Week_images_table (name, images) VALUES (:name, :images)");
    query.bindValue(":name", dayImageList->getName());
    query.bindValue(":images", jsonString);

    if (!query.exec()) {
        qDebug() << "Error inserting day image list into Week_images_table:" << query.lastError().text();
        return false;
    }
    // Отримуємо останній доданий ID та встановлюємо його у не `const` об'єкті
    dayImageList->setId(query.lastInsertId().toInt());

    return true;
}

QVector<DayImageList> SqliteDBManager::getAllDayImageLists(){
    QVector<DayImageList> dayImageLists;

    QSqlQuery query;
    if (!query.exec("SELECT id, name, images FROM Week_images_table")) {
        qDebug() << "Error retrieving all day image lists:" << query.lastError().text();
        return dayImageLists; // Return an empty array in case of error
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString jsonImages = query.value(2).toString();

        DayImageList dayImageList;
        dayImageList.fromJsonString(jsonImages);
        dayImageList.setId(id);
        dayImageList.setName(name); // Set the name
        dayImageLists.append(dayImageList);
    }

    return dayImageLists;
}

DayImageList SqliteDBManager::findDayImageListById(int id) {
    QSqlQuery query;
    query.prepare("SELECT id, name, images FROM Week_images_table WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error retrieving day image list:" << query.lastError().text();
        return DayImageList(); // Return a default-constructed DayImageList in case of error
    }

    if (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        QString jsonImages = query.value(2).toString();

        DayImageList dayImageList;
        dayImageList.fromJsonString(jsonImages);
        dayImageList.setId(id);
        dayImageList.setName(name); // Set the name
        return dayImageList;
    }

    return DayImageList(); // Return a default-constructed DayImageList if no record with such id is found
}

bool SqliteDBManager::updateDayImageList(DayImageList* dayImageList) {
    if (!dayImageList) {
        qDebug() << "Null pointer received for day image list!";
        return false;
    }

    // Перевірка, чи відомий ідентифікатор списку
    if (dayImageList->getId() == -1) {
        qDebug() << "Unknown id for day image list!";
        return false;
    }

    // Серіалізація списку у формат JSON
    QString jsonString = dayImageList->toJsonString();

    // Оновлення запису в базі даних
    QSqlQuery query;
    query.prepare("UPDATE Week_images_table SET name = :name, images = :images WHERE id = :id");
    query.bindValue(":name", dayImageList->getName());
    query.bindValue(":images", jsonString);
    query.bindValue(":id", dayImageList->getId());

    if (!query.exec()) {
        qDebug() << "Error updating day image list:" << query.lastError().text();
        return false;
    }

    return true;
}
