#ifndef WEEKVIEWIMAGESLIDER_H
#define WEEKVIEWIMAGESLIDER_H
#include "uiimageslider.h"

class WeekViewImageSlider : public ImageSlider
{
    Q_OBJECT
public:
    WeekViewImageSlider(const QMap<DayOfWeek, int> &imageIds, const WidgetGeometry &geometry, QWidget *parent);
private:
    const QStringList days = {"Other days","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    void showNextImage() override;
    void showPrevImage() override;

   QMap<DayOfWeek, int> imageIds;
   QLabel* lableDay;


   QString getURLFromId(int index);
};

#endif // WEEKVIEWIMAGESLIDER_H
