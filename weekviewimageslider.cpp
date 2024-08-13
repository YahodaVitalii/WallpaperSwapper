#include "weekviewimageslider.h"

WeekViewImageSlider::WeekViewImageSlider(const QMap<QString, int> &imageIds, const WidgetGeometry &geometry, QWidget *parent)
    : ImageSlider(geometry,parent),imageIds(imageIds)
{
    imageListSize = imageIds.size();

   CreateLableWithImage(lableGeometry);
   CreateNextButton(nextButtonIco,nextButtonSizeTimeTabs);
   CreatePrevButton(prevButtonIco,prevButtonSizeTimeTabs);

  lableDay = uiElementFactory->CreateLableWithText(this,days[currentIndex],290,65);

   updateImage(getURLFromId(currentIndex));
}

void WeekViewImageSlider::showNextImage()
{
    currentIndex = (currentIndex + 1) % imageListSize;

    if(imageIds[days[currentIndex]] > 0 && imageIds[days[currentIndex]] < 8){
    updateImage(getURLFromId(currentIndex));
    lableDay->setText(days[currentIndex]);
    }
    else{
       showNextImage();

    }
}
void WeekViewImageSlider::showPrevImage()
{
    currentIndex = (currentIndex - 1 + imageListSize) % imageListSize;

    if(imageIds[days[currentIndex]] > 0 && imageIds[days[currentIndex]] < 8){
       updateImage(getURLFromId(currentIndex));
        lableDay->setText(days[currentIndex]);
    }else{
        showPrevImage();
    }

}

QString WeekViewImageSlider::getURLFromId(int index)
{
    return  imageList->GetImageByIndex(imageIds[days[index]]).getUrl();
}
