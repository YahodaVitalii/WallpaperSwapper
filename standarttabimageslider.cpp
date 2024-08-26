#include "standarttabimageslider.h"

StandartTabImageSlider::StandartTabImageSlider(const WidgetGeometry &geometry, QWidget *parent)
    : ImageSlider(geometry,parent)
{
    imageListSize = imageList->getsizeOfImages();

    CreateLableWithImage(lableGeometry);
    CreateNextButton(nextButtonIco,WidgetGeometry(65,65,490,140));
    CreatePrevButton(prevButtonIco,WidgetGeometry(65,65,65,140));
    createThumbnails();

    updateImage(getURLFromId(currentIndex));
    updateThumbnails();
}

void StandartTabImageSlider::ChangeCurrentImage(int index)
{
    currentIndex = index ;
    imageListSize = imageList->getsizeOfImages();
    updateImage(getURLFromId(currentIndex));
    updateThumbnails();
}

int StandartTabImageSlider::GetCurrentIndex() const
{
return currentIndex;
}

void StandartTabImageSlider::showNextImage()
{
    currentIndex = (currentIndex + 1) % imageListSize;
    updateImage(getURLFromId(currentIndex));
    updateThumbnails();
}

void StandartTabImageSlider::showPrevImage()
{
    currentIndex = (currentIndex - 1 + imageListSize) % imageListSize;
    updateImage(getURLFromId(currentIndex));
    updateThumbnails();
}

QString StandartTabImageSlider::getURLFromId(int index)
{
    if(imageListSize > 0){
        return imageList->GetImageByIndex(index).getUrl();
    }
    return "";
}

void StandartTabImageSlider::updateThumbnails()
{
    if (imageListSize > 0) {
        // Оновлення мініатюр
        QPixmap pixmap1(getURLFromId((currentIndex - 2 + imageListSize) % imageListSize));
        previousSecondThumbnail->setPixmap(pixmap1);

        QPixmap pixmap2(getURLFromId((currentIndex - 1 + imageListSize) % imageListSize));
        previousFirstThumbnail->setPixmap(pixmap2);

        QPixmap pixmap3(getURLFromId((currentIndex + 1) % imageListSize));
        nextFirstThumbnail->setPixmap(pixmap3);

        QPixmap pixmap4(getURLFromId((currentIndex + 2) % imageListSize));
        nextSecondThumbnail->setPixmap(pixmap4);
    }
}

void StandartTabImageSlider::createThumbnails()
{
    previousSecondThumbnail = new CustomLabel(this);
    previousSecondThumbnail->setGeometry(155, 330, 80, 80);

    previousFirstThumbnail = new CustomLabel(this);
    previousFirstThumbnail->setGeometry(240, 330, 80, 80);

    nextFirstThumbnail = new CustomLabel(this);
    nextFirstThumbnail->setGeometry(325, 330, 80, 80);

    nextSecondThumbnail = new CustomLabel(this);
    nextSecondThumbnail->setGeometry(410, 330, 80, 80);
}

