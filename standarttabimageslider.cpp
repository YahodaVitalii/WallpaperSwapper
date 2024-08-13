#include "standarttabimageslider.h"

StandartTabImageSlider::StandartTabImageSlider(const WidgetGeometry &geometry, QWidget *parent)
    : ImageSlider(geometry,parent)
{
    imageListSize = imageList->getsizeOfImages();

    CreateLableWithImage(lableGeometry);
    CreateNextButton(nextButtonIco,WidgetGeometry(65,65,490,140));
    CreatePrevButton(prevButtonIco,WidgetGeometry(65,65,65,140));
if(imageListSize > 0){
    updateImage(getURLFromId(currentIndex));
}
}

void StandartTabImageSlider::ChangeCurrentImage(int index)
{
currentIndex = index ;
imageListSize = imageList->getsizeOfImages();
updateImage(getURLFromId(currentIndex));
}

void StandartTabImageSlider::showNextImage()
{
    currentIndex = (currentIndex + 1) % imageListSize;
    updateImage(getURLFromId(currentIndex));
}

void StandartTabImageSlider::showPrevImage()
{
    currentIndex = (currentIndex - 1 + imageListSize) % imageListSize;
    updateImage(getURLFromId(currentIndex));
}

QString StandartTabImageSlider::getURLFromId(int index)
{
    return imageList->GetImageByIndex(index).getUrl();
}

