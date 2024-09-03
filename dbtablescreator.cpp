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
            createTableMoodImageList();
            createTableEmodji();
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
                    " url TEXT NOT NULL UNIQUE, "
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
                    "time_interval TIMESTAMP NOT NULL)"
                    )) {
        throw WSExeptions("Error creating table RandomImageLists: " + query.lastError().text());
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
        throw WSExeptions("Error creating table RandomImageListImages: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableWeekImageLists() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE WeekImageList ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name TEXT NOT NULL)")) {
        throw WSExeptions("Error creating table WeekImagesList: " + query.lastError().text());
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
        throw WSExeptions("Error creating table WeekImages: " + query.lastError().text());
    }
}

void DBTablesCreator::createTableDayImageLists() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE DayImageList ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "name TEXT)")) {
        throw WSExeptions("Error creating table DayImageList: " + query.lastError().text());
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
        throw WSExeptions("Error creating table DayImages: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableMoodImageList() {
    QSqlQuery query;
    if (!query.exec("CREATE TABLE MoodImageList ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "emodjiId INTEGER, "
                    "imageId INTEGER, "
                    "FOREIGN KEY(emodjiId) REFERENCES Emodji(id), "  // Added a comma
                    "FOREIGN KEY(imageId) REFERENCES ImagesTable(id))")) {
        throw WSExeptions("Error creating table MoodImageList: " + query.lastError().text());
    }
}
void DBTablesCreator::createTableEmodji() {
    QSqlQuery query;

    // Create the Emodji table with only id and emodji fields
    if (!query.exec("CREATE TABLE Emodji ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "emodji TEXT)")) {
        throw WSExeptions("Error creating table Emodji: " + query.lastError().text());
    }

    // Load emojis from the resource file and insert them into the table
    qDebug()<<"1";
    QFile file(":/resource/emojis.txt");
    qDebug()<<"2";
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw WSExeptions("Error opening emoji resource file.");
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString emodji = in.readLine().trimmed();
        if (!emodji.isEmpty()) {
            query.prepare("INSERT INTO Emodji (emodji) VALUES (:emodji)");  // Corrected to insert into Emodji table
            query.bindValue(":emodji", emodji);
            if (!query.exec()) {
                qDebug() << "Error inserting emoji:" << query.lastError().text();
            }
        }
    }
    file.close();
}
