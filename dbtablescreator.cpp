#include "dbtablescreator.h"

bool DBTablesCreator::BuildTables()
{
    try {
            createTableImage();
            createTableRandomImageLists();
            createTableWeekImages();
            createTableDayImages();
        } catch (const WSExeptions& e) {
            qDebug() << "Database: error in createTables: " << e.what();
            return false;
        }
        return true;
    }
void DBTablesCreator::createTableImage() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE  Images  ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    " name  VARCHAR(255) NOT NULL, "
                    " url TEXT NOT NULL, "
                    " height INTEGER NOT NULL, "
                    " width INTEGER NOT NULL"
                    " )"
                    )) {
        throw WSExeptions("Error creating table  Images" + query.lastError().text());
    }
}

void DBTablesCreator::createTableRandomImageLists() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE RandomImageLists ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name VARCHAR(255) NOT NULL,"
                    "time_interval TIMESTAMP NOT NULL, "
                    "image_array TEXT NOT NULL)"
                    )) {
        throw WSExeptions("Error creating table RandomImageLists: " + query.lastError().text());
    }
}

void DBTablesCreator::createTableWeekImages() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE Week_images_table ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT,"
                    "images TEXT)")) {
        throw WSExeptions("Error creating table Week_images_table: " + query.lastError().text());
    }
}

void DBTablesCreator::createTableDayImages() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE Day_images_table ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT, "
                    "images TEXT)")) {
        throw WSExeptions("Error creating table Day_images_table: " + query.lastError().text());
    }
}
