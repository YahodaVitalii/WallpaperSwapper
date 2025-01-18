#include "enums/dayofweek.h"

QString dayOfWeekToString(DayOfWeek day) {
    switch(day) {
        case DayOfWeek::OtherDays: return "Other days";
        case DayOfWeek::Monday: return "Monday";
        case DayOfWeek::Tuesday: return "Tuesday";
        case DayOfWeek::Wednesday: return "Wednesday";
        case DayOfWeek::Thursday: return "Thursday";
        case DayOfWeek::Friday: return "Friday";
        case DayOfWeek::Saturday: return "Saturday";
        case DayOfWeek::Sunday: return "Sunday";
        default: return "";
    }
}
