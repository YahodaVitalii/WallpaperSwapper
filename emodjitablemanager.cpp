#include "emodjitablemanager.h"

EmodjiTableManager::EmodjiTableManager()
{
    if (isTableEmpty()) {
            loadEmojisFromFile(":/resource/emojis.txt");
        }
}
void EmodjiTableManager::insertEmodji(const QString& emodji) {
    QSqlQuery query;
    query.prepare("INSERT INTO Emodji (emodji) VALUES (:emodji)");
    query.bindValue(":emodji", emodji);
    if (!query.exec()) {
        qDebug() << "Error inserting emoji:" << query.lastError().text();
    }
}

void EmodjiTableManager::loadEmojisFromFile(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw WSExceptions("Error opening emoji resource file.");
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString emodji = in.readLine().trimmed();
        if (!emodji.isEmpty()) {
            insertEmodji(emodji);  // Викликаємо окрему функцію для вставки
        }
    }
    file.close();
}
QMap<int, QString> EmodjiTableManager::getAllEmodji() {
    QMap<int, QString> emodjiMap;  // Створюємо карту для зберігання id та емодзі
    QSqlQuery query;

    if (!query.exec("SELECT id, emodji FROM Emodji")) {
        throw WSExceptions("Error fetching emodji: " + query.lastError().text());
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        QString emodji = query.value(1).toString();
        emodjiMap.insert(id, emodji);  // Додаємо в мапу
    }

    return emodjiMap;  // Повертаємо мапу з даними
}
QString EmodjiTableManager::getEmodjiById(int id) {
    QSqlQuery query;
    query.prepare("SELECT emodji FROM Emodji WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec() || !query.next()) {
        throw WSExceptions("Error fetching emodji by id: " + query.lastError().text());
    }

    return query.value(0).toString();  // Повертаємо емодзі
}

bool EmodjiTableManager::isTableEmpty()
{
    QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM Emodji");

        if (!query.exec() || !query.next()) {
            qDebug() << "Error checking if table is empty:" << query.lastError().text();
            return false;  // Якщо виникла помилка, вважаємо, що таблиця не пуста
        }

        int count = query.value(0).toInt();
        return count == 0;  // Якщо кільк
}
