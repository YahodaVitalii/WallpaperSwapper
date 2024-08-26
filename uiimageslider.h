#ifndef UIIMAGESLIDER_H
#define UIIMAGESLIDER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QHBoxLayout>
#include "SQLTableImageList.h"
#include "widgetgeometry.h"// Підключення для доступу до зображень
#include "uielementfactory.h"
#include "style.h"

class ImageSlider : public QWidget {
    Q_OBJECT

public:
    explicit ImageSlider(const WidgetGeometry& geometry, QWidget* parent = nullptr);
    ~ImageSlider();
    void CreateLableWithImage(const WidgetGeometry& geometry);
    void CreateNextButton(const QString iconURL,const WidgetGeometry& geometry);
    void CreatePrevButton(const QString iconURL,const WidgetGeometry& geometry);
protected slots:
    void NextButtonClicked();
    void PrevButtonClicked();

protected:
    virtual void showNextImage()=0;
    virtual void showPrevImage()=0;

    void updateImage(QString url);

    int imageListSize;

    const WidgetGeometry &lableGeometry;
    const WidgetGeometry nextButtonSizeTimeTabs={35,35,180,45};
    const WidgetGeometry prevButtonSizeTimeTabs={35,35,5,45};

    const QString nextButtonIco = ":/resource/SliderRightArrow.png";
    const QString prevButtonIco = ":/resource/SliderLeftArrow.png";

  int currentIndex;

    UIElementFactory* uiElementFactory;
    QLabel* imageLabel;
    QTimer* slideTimer;
    QPushButton* nextButton;
    QPushButton* prevButton;
    SQLTableImageList* imageList;
};

#endif // UIIMAGESLIDER_H
