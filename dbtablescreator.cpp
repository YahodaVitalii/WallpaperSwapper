#include "dbtablescreator.h"

bool DBTablesCreator::BuildTables()
{
    try {
            createTableImage();
            createTableRandomImageLists();
            createTableRandomImages();
            createTableWeekImageLists();
            createTableWeekImages();
            createTableDayImageLists();
            createTableDayImages();
            createTableMoodImage();
            createTableEmodji();
        } catch (const WSExceptions& e) {
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
                    " url TEXT NOT NULL UNIQUE, "
                    " height INTEGER NOT NULL, "
                    " width INTEGER NOT NULL"
                    " )"
                    )) {
        throw WSExceptions("Error creating table  Images" + query.lastError().text());
    }
}

void DBTablesCreator::createTableRandomImageLists() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE RandomImageLists ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name VARCHAR(255) NOT NULL,"
                    "time_interval TIMESTAMP NOT NULL)"
                    )) {
        throw WSExceptions("Error creating table RandomImageLists: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableRandomImages() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE RandomImages ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "random_list_id INTEGER NOT NULL, "
                    "image_id INTEGER NOT NULL, "
                    "FOREIGN KEY(random_list_id) REFERENCES RandomImageLists(id) ON DELETE CASCADE, "
                    "FOREIGN KEY(image_id) REFERENCES Images(id) ON DELETE CASCADE)"
                    )) {
        throw WSExceptions("Error creating table RandomImageListImages: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableWeekImageLists() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE WeekImageList ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL)")) {
        throw WSExceptions("Error creating table WeekImagesList: " + query.lastError().text());
    }
}

void DBTablesCreator::createTableWeekImages() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE WeekImages ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "list_id INTEGER NOT NULL, "
                    "monday INTEGER, "
                    "tuesday INTEGER, "
                    "wednesday INTEGER, "
                    "thursday INTEGER, "
                    "friday INTEGER, "
                    "saturday INTEGER, "
                    "sunday INTEGER, "
                    "other_days INTEGER, "
                    "FOREIGN KEY(list_id) REFERENCES WeekImagesList(id) ON DELETE CASCADE, "
                    "FOREIGN KEY(monday) REFERENCES Images(id) ON DELETE SET NULL, "
                    "FOREIGN KEY(tuesday) REFERENCES Images(id) ON DELETE SET NULL, "
                    "FOREIGN KEY(wednesday) REFERENCES Images(id) ON DELETE SET NULL, "
                    "FOREIGN KEY(thursday) REFERENCES Images(id) ON DELETE SET NULL, "
                    "FOREIGN KEY(friday) REFERENCES Images(id) ON DELETE SET NULL, "
                    "FOREIGN KEY(saturday) REFERENCES Images(id) ON DELETE SET NULL, "
                    "FOREIGN KEY(sunday) REFERENCES Images(id) ON DELETE SET NULL, "
                    "FOREIGN KEY(other_days) REFERENCES Images(id) ON DELETE SET NULL"
                    ")")) {
        throw WSExceptions("Error creating table WeekImages: " + query.lastError().text());
    }
}

void DBTablesCreator::createTableDayImageLists() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE DayImageList ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT)")) {
        throw WSExceptions("Error creating table DayImageList: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableDayImages() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE DayImages ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "timeStart TEXT, "
                    "timeEnd TEXT, "
                    "imageID INTEGER, "
                    "listId INTEGER, "
                    "FOREIGN KEY(imageID) REFERENCES ImagesTable(id), "
                    "FOREIGN KEY(listId) REFERENCES WeekImagesList(id))")) {
        throw WSExceptions("Error creating table DayImages: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableMoodImage() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE MoodImageList ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "emodjiId INTEGER UNIQUE, "
                    "imageId INTEGER, "
                    "FOREIGN KEY(emodjiId) REFERENCES Emodji(id), "  // Added a comma
                    "FOREIGN KEY(imageId) REFERENCES ImagesTable(id))")) {
        throw WSExceptions("Error creating table MoodImageList: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableEmodji() {
    QSqlQuery query;

    if (!query.exec("CREATE TABLE Emodji ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "emodji TEXT)")) {
        throw WSExceptions("Error creating table Emodji: " + query.lastError().text());
    }

}
