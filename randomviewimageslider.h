#ifndef RANDOMVIEWIMAGESLIDER_H
#define RANDOMVIEWIMAGESLIDER_H
#include "uiimageslider.h"


class RandomViewImageSlider : public ImageSlider
{
    Q_OBJECT
public:
    RandomViewImageSlider(const QVector<int>& imageIds, const WidgetGeometry& geometry, QWidget* parent = nullptr);
private:
    void showNextImage() override;
    void showPrevImage() override;

    QVector<int> imageIds;

    QString getURLFromId(int index);
};

#endif // RANDOMVIEWIMAGESLIDER_H
