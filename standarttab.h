#ifndef STANDARTTAB_H
#define STANDARTTAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include <Windows.h>
#include <QMessageBox>
#include "sqlitedbmanager.h"
#include "dialogwindowlistofimage.h"
#include "wallpapersetter.h"
#include "dialogwindowcontroller.h"

#include "imagelist.h"
namespace Ui {
class StandartTab;
}

class StandartTab : public QWidget
{
    Q_OBJECT

public:
    explicit StandartTab(DBManager* dbManager, ImageList* imageList, QWidget *parent = nullptr);
    ~StandartTab();

    void showImage(int index);
    void previousImage();
    void nextImage();

    void setStandartTabStyle();
    void setSliderButtonIcon();

    void displayImageInLabel(QLabel* label, const QString& filePath);

    bool setWallpaper(const QString &imagePath);
private slots:
    void on_StandartTabChooseButton_clicked();
    void on_StandartTabAddButton_clicked();
    void on_StandartTabSetButton_clicked();

    void on_SliderLeftArrow_clicked();
    void on_SliderRightArrow_clicked();
    void on_StandartTabDeleteButton_clicked();
public slots:
    void updateImage(int index);
private:
    Ui::StandartTab *ui;

    DBManager* dbManager;
    ImageList* imageList;
    ImageLoader* imageLoader;
    WallpaperSetter* wallpaperSetter;
    //DialogWindowListOfImage *dialogWindowListOfImage;
     DialogWindowController* dialogWindowController;

    InterfaceAddition* interfaceAddition;
    UIElementEventHandler *uiElementEventHandler;
    int currentIndex = 0;
};

#endif // STANDARTTAB_H
