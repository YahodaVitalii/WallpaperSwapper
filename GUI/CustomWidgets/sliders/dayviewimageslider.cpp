#include "dayviewimageslider.h"

DayViewImageSlider::DayViewImageSlider(const QVector<TimeRangeImage> &imageIds, const WidgetGeometry &geometry, QWidget *parent)
    : ImageSlider(geometry,parent),imageIds(imageIds)
{
    imageListSize = imageIds.size();

   CreateLableWithImage(lableGeometry);
   CreateNextButton(nextButtonIco,nextButtonSizeTimeTabs);
   CreatePrevButton(prevButtonIco,prevButtonSizeTimeTabs);

   startTimeLable =  uiElementFactory->CreateLableWithText(this,imageIds[currentIndex].startTime,290,75);
   endTimeLable =  uiElementFactory->CreateLableWithText(this,imageIds[currentIndex].endTime,340,75);

   updateImage(getURLFromId(currentIndex));
}

void DayViewImageSlider::showNextImage()
{
    currentIndex = (currentIndex + 1) % imageListSize;
  updateImage(getURLFromId(currentIndex));
  startTimeLable->setText(imageIds[currentIndex].startTime);
  endTimeLable->setText(imageIds[currentIndex].endTime);
}

void DayViewImageSlider::showPrevImage()
{
    currentIndex = (currentIndex - 1 + imageListSize) % imageListSize;
updateImage(getURLFromId(currentIndex));
startTimeLable->setText(imageIds[currentIndex].startTime);
endTimeLable->setText(imageIds[currentIndex].endTime);
}

QString DayViewImageSlider::getURLFromId(int index)
{
return imageList->GetImageByIndex(imageIds[index].imageId).getUrl();
}



