#ifndef TIMERANGEIMAGE_H
#define TIMERANGEIMAGE_H
struct TimeRangeImage {
    QString startTime;
    QString endTime;
    int imageId;
    int id;

    TimeRangeImage() : startTime(""), endTime(""), imageId(-1), id(-1) {}

    TimeRangeImage(const QString& start, const QString& end, int imageId, int id)
        : startTime(start), endTime(end), imageId(imageId), id(id) {}
};

#endif // TIMERANGEIMAGE_H
