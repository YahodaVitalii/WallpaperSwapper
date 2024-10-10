#ifndef EMODJITABLEMANAGER_H
#define EMODJITABLEMANAGER_H
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include "wsexception.h"
#include <QSqlError>
#include <QFile>
class EmodjiTableManager
{
public:
    EmodjiTableManager();
    void insertEmodji(const QString& emodji);
    void loadEmojisFromFile(const QString& filePath);
    QMap<int, QString> getAllEmodji();
    QString getEmodjiById(int id);
     bool isTableEmpty();
};

#endif // EMODJITABLEMANAGER_H
