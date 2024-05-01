#ifndef STANDARTTAB_H
#define STANDARTTAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include <QMessageBox>
#include "sqlitedbmanager.h"
#include <Windows.h>
#include "dialogwindowlistofimage.h"

#include "imagemanager.h"
namespace Ui {
class StandartTab;
}

class StandartTab : public QWidget
{
    Q_OBJECT

public:
    explicit StandartTab(DBManager* dbManager,QWidget *parent = nullptr);
    ~StandartTab();

    void showImage(int index);
    void previousImage();
    void nextImage();
    //QVector<WlapperImage> images;

    void setStandartTabStyle();
    void setSliderButtonIcon();

    QImage loadImage(const QString& fileName);
    std::unique_ptr<WlapperImage> createWlapperImage(const QString& fileName, const QImage& image);
    void displayImageInLabel(QLabel* label, const QString& filePath);

    bool setWallpaper(const QString &imagePath);
private slots:
    void on_StandartTabChooseButton_clicked();
    void on_StandartTabAddButton_clicked();
    void on_StandartTabSetButton_clicked();

    void on_SliderLeftArrow_clicked();
    void on_SliderRightArrow_clicked();
    void on_StandartTabDeleteButton_clicked();

private:
    Ui::StandartTab *ui;

    DBManager* dbManager;
    ImageManager* imageManager;

    DialogWindowListOfImage* dialogWindowListOfImage;

    int currentIndex = 0;
};

#endif // STANDARTTAB_H
