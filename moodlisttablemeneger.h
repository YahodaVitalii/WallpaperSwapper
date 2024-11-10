#ifndef MOODLISTTABLEMENEGER_H
#define MOODLISTTABLEMENEGER_H

#include "listtablemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QPair>
#include "wsexception.h"

class MoodListTableMeneger : public ListTableManager<QPair<int, int>, QMap<int, int>> {
public:
    MoodListTableMeneger();

    // Implement abstract methods from ListTableManager
    bool insertIntoTable(const QPair<int, int>& moodImage) override;
    QMap<int, int> getAllRecords() override;
    bool updateList(const QPair<int, int>& moodImage) override;

    QPair<int,int> findListById(int emodjiId) override;
    bool deleteMoodImage(int emodjiId, int imageId);
};

#endif // MOODLISTTABLEMENEGER_H
