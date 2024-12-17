#ifndef STANDARTTABIMAGESLIDER_H
#define STANDARTTABIMAGESLIDER_H
#include "uiimageslider.h"
#include "customlabel.h"

class StandartTabImageSlider : public ImageSlider
{
    Q_OBJECT
public:
    StandartTabImageSlider(const WidgetGeometry& geometry, QWidget* parent = nullptr);
    void ChangeCurrentImage(int index);
    int GetCurrentIndex() const;
private:
    void showNextImage() override;
    void showPrevImage() override;
    QString getURLFromId(int index);
    void updateThumbnails();
    void createThumbnails();

    CustomLabel* previousSecondThumbnail;
    CustomLabel* previousFirstThumbnail;
    CustomLabel* nextFirstThumbnail;
    CustomLabel* nextSecondThumbnail;

};
#endif // STANDARTTABIMAGESLIDER_H
