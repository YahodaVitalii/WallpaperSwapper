#ifndef DAYOFWEEK_H
#define DAYOFWEEK_H

#include <QString>

enum class DayOfWeek {
    OtherDays,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
    Count  // для визначення кількості днів
};

QString dayOfWeekToString(DayOfWeek day);

#endif
