#include "weekviewimageslider.h"

WeekViewImageSlider::WeekViewImageSlider(const QMap<DayOfWeek, int> &imageIds, const WidgetGeometry &geometry, QWidget *parent)
    : ImageSlider(geometry, parent), imageIds(imageIds)
{
    imageListSize = imageIds.size();

    CreateLableWithImage(lableGeometry);
    CreateNextButton(nextButtonIco, nextButtonSizeTimeTabs);
    CreatePrevButton(prevButtonIco, prevButtonSizeTimeTabs);

    lableDay = uiElementFactory->CreateLableWithText(this, dayOfWeekToString(static_cast<DayOfWeek>(currentIndex)), 290, 65);

    updateImage(getURLFromId(currentIndex));  // Тепер передаємо int
}

void WeekViewImageSlider::showNextImage()
{
    currentIndex = (currentIndex + 1) % imageListSize;
    DayOfWeek currentDay = static_cast<DayOfWeek>(currentIndex);

    if (imageIds[currentDay] > 0 && imageIds[currentDay] < 8) {
        updateImage(getURLFromId(currentIndex));  // Передаємо int
        lableDay->setText(dayOfWeekToString(currentDay));
    } else {
        showNextImage();
    }
}

void WeekViewImageSlider::showPrevImage()
{
    currentIndex = (currentIndex - 1 + imageListSize) % imageListSize;
    DayOfWeek currentDay = static_cast<DayOfWeek>(currentIndex);

    if (imageIds[currentDay] > 0 && imageIds[currentDay] < 8) {
        updateImage(getURLFromId(currentIndex));  // Передаємо int
        lableDay->setText(dayOfWeekToString(currentDay));
    } else {
        showPrevImage();
    }
}

QString WeekViewImageSlider::getURLFromId(int index)  // Параметр залишився int
{
    DayOfWeek day = static_cast<DayOfWeek>(index);  // Конвертуємо int в DayOfWeek
    return imageList->GetImageByIndex(imageIds[day]).getUrl();
}
