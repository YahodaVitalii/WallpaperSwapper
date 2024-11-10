#include "emodjitablemanager.h"

EmodjiTableManager::EmodjiTableManager() {
    if (isTableEmpty()) {
        loadEmojisFromFile(":/resource/emojis.txt");
    }
}

bool EmodjiTableManager::insertIntoTable(const QString& emodji) {
    QSqlQuery query;
    query.prepare("INSERT INTO Emodji (emodji) VALUES (:emodji)");
    query.bindValue(":emodji", emodji);
    return executeQuery(query);  // Використовуємо executeQuery базового класу
}

QMap<int, QString> EmodjiTableManager::getAllRecords() {
    QMap<int, QString> emodjiMap;
    QSqlQuery query;

    if (!query.exec("SELECT id, emodji FROM Emodji")) {
        throw WSException("Error fetching emodji: " + query.lastError().text());
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString emodji = query.value(1).toString();
        emodjiMap.insert(id, emodji);
    }

    return emodjiMap;
}

QString EmodjiTableManager::getEmodjiById(int id) {
    QSqlQuery query;
    query.prepare("SELECT emodji FROM Emodji WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        throw WSException("Error fetching emodji by id: " + query.lastError().text());
    }

    return query.value(0).toString();
}

bool EmodjiTableManager::isTableEmpty() {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM Emodji");

    if (!query.exec() || !query.next()) {
        qDebug() << "Error checking if table is empty:" << query.lastError().text();
        return false;
    }

    int count = query.value(0).toInt();
    return count == 0;
}

void EmodjiTableManager::loadEmojisFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw WSException("Error opening emoji resource file.");
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString emodji = in.readLine().trimmed();
        if (!emodji.isEmpty()) {
            insertIntoTable(emodji);
        }
    }
    file.close();
}
