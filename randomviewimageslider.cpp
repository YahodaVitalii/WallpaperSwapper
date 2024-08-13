#include "randomviewimageslider.h"

RandomViewImageSlider::RandomViewImageSlider(const QVector<int> &imageIds, const WidgetGeometry &geometry, QWidget *parent)
    : ImageSlider(geometry,parent),imageIds(imageIds)
{
 imageListSize = imageIds.size();

CreateLableWithImage(lableGeometry);
CreateNextButton(nextButtonIco,nextButtonSizeTimeTabs);
CreatePrevButton(prevButtonIco,prevButtonSizeTimeTabs);

updateImage(getURLFromId(currentIndex));
}

void RandomViewImageSlider::showNextImage()
{
    currentIndex = (currentIndex + 1) % imageListSize;
  updateImage(getURLFromId(currentIndex));
}

void RandomViewImageSlider::showPrevImage()
{
      currentIndex = (currentIndex - 1 + imageListSize) % imageListSize;
 updateImage(getURLFromId(currentIndex));
}

QString RandomViewImageSlider::getURLFromId(int index)
{
return imageList->GetImageByIndex(imageList->findImageById(imageIds[index])).getUrl();
}
