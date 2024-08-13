#ifndef DAYVIEWIMAGESLIDER_H
#define DAYVIEWIMAGESLIDER_H
#include "uiimageslider.h"

class DayViewImageSlider : public ImageSlider
{
    Q_OBJECT
public:
    DayViewImageSlider(const QVector<TimeRangeImage>& imageIds, const WidgetGeometry& geometry, QWidget* parent = nullptr);
private:
    void showNextImage() override;
    void showPrevImage() override;

    QVector<TimeRangeImage> imageIds;
    QLabel* startTimeLable;
    QLabel* endTimeLable;


    QString getURLFromId(int index);
};

#endif // DAYVIEWIMAGESLIDER_H
