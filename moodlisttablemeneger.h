#ifndef MOODLISTTABLEMENEGER_H
#define MOODLISTTABLEMENEGER_H

#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QPair>
#include "wsexception.h"

class MoodListTableMeneger {
public:
    // Конструктор
    MoodListTableMeneger();

    // Функція для вставки нового запису у MoodImageList
    bool insertMoodImage(int emodjiId, int imageId);

    // Функція для отримання всіх записів MoodImageList
    QMap<int, int> getAllMoodImages();

     // Функція для отримання imageId за emodjiId
     int findImageByEmodjiId(int emodjiId);
    // Функція для оновлення MoodImage
    bool updateMoodImage(int emodjiId, int newImageId);

    // Функція для видалення запису за emodjiId та imageId
    bool deleteMoodImage(int emodjiId, int imageId);

};

#endif // MOODLISTTABLEMENEGER_H
