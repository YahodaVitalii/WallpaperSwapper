#ifndef EMODJITABLEMANAGER_H
#define EMODJITABLEMANAGER_H
#include <QSqlError>
#include <QFile>
#include "wsexception.h"
#include "dbtablemanager.h"

// Наслідуємо EmodjiTableManager від DBTableManager
class EmodjiTableManager : public DBTableManager<QString, QMap<int, QString>>
{
public:
    EmodjiTableManager();

    // Реалізуємо абстрактні методи базового класу
    bool insertIntoTable(const QString& emodji) override;
    QMap<int, QString> getAllRecords() override;

    QString getEmodjiById(int id);
    bool isTableEmpty();

private:
    void loadEmojisFromFile(const QString& filePath);
};

#endif // EMODJITABLEMANAGER_H
