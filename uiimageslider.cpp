#include "uiimageslider.h"
ImageSlider::ImageSlider(const WidgetGeometry &geometry, QWidget* parent)
    : QWidget(parent),  lableGeometry(geometry),currentIndex(0) {
    imageList = SQLTableImageList::getInstance();
    uiElementFactory = new UIElementFactory();

    //    slideTimer = new QTimer(this);
    //    connect(slideTimer, &QTimer::timeout, this, &ImageSlider::showNextImage);
    //    slideTimer->start(3000); // Перемикання зображень кожні 3 секунди
}

ImageSlider::~ImageSlider() {
    // slideTimer->stop();
}

void ImageSlider::CreateLableWithImage(const WidgetGeometry &geometry)
{
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(geometry.width, geometry.height);
    imageLabel->move(geometry.xPos,geometry.yPos);
    imageLabel->setScaledContents(true);

}

void ImageSlider::CreateNextButton(const QString iconURL, const WidgetGeometry &geometry)
{
    nextButton = new QPushButton(this);
    nextButton->move(geometry.xPos,geometry.yPos);
    nextButton->setIcon(QIcon(iconURL));
    nextButton->setIconSize(QSize(geometry.width, geometry.height ));
    nextButton->setStyleSheet(Style::getSliderStyle());
    connect(nextButton, &QPushButton::clicked, this, &ImageSlider::NextButtonClicked);
}

void ImageSlider::CreatePrevButton(const QString iconURL, const WidgetGeometry &geometry)
{
    prevButton = new QPushButton(this);
    prevButton->move(geometry.xPos,geometry.yPos);
    prevButton->setIcon(QIcon(iconURL));
    prevButton->setIconSize(QSize(geometry.width, geometry.height ));
    prevButton->setStyleSheet(Style::getSliderStyle());
    connect(prevButton, &QPushButton::clicked, this, &ImageSlider::PrevButtonClicked);
}

void ImageSlider::NextButtonClicked()
{  
    showNextImage();
}
void ImageSlider::PrevButtonClicked()
{
    showPrevImage();
}

void ImageSlider::updateImage(QString url) {
    if (currentIndex >= 0 && currentIndex < imageListSize) {
        QPixmap pixmap(url);
        imageLabel->setPixmap(pixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio));
    }
}



