#ifndef STANDARTTABIMAGESLIDER_H
#define STANDARTTABIMAGESLIDER_H
#include "uiimageslider.h"

class StandartTabImageSlider : public ImageSlider
{
    Q_OBJECT
public:
    StandartTabImageSlider(const WidgetGeometry& geometry, QWidget* parent = nullptr);
    void ChangeCurrentImage(int index);
private:
    void showNextImage() override;
    void showPrevImage() override;

    //QVector<int> imageIds;

    QString getURLFromId(int index);

};
#endif // STANDARTTABIMAGESLIDER_H
