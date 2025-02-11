#ifndef STANDARTTAB_H
#define STANDARTTAB_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QFileDialog>
#include <Windows.h>
#include <QMessageBox>
#include "DB/sqlitedbmanager.h"
#include "windowlistofimage.h"
#include "core/wallpapersetter.h"
#include "GUI/service/dialogwindowcontroller.h"
#include "models/imagelist.h"
#include "GUI/CustomWidgets/sliders/standarttabimageslider.h"
namespace Ui {
class StandartTab;
}

class StandartTab : public QWidget
{
    Q_OBJECT

public:
    explicit StandartTab(ImageList* imageList, QWidget *parent = nullptr);
    ~StandartTab();
    void setStandartTabStyle();
private slots:
    void on_StandartTabChooseButton_clicked();
    void on_StandartTabAddButton_clicked();
    void on_StandartTabSetButton_clicked();
    void on_StandartTabDeleteButton_clicked();
public slots:
    void updateImage(int index);
private:
    Ui::StandartTab *ui;

    DBManager* dbManager;
    ImageList* imageList;
    ImageLoader* imageLoader;
    WallpaperSetter* wallpaperSetter;
    DialogWindowController* dialogWindowController;

    StandartTabImageSlider* imageSlider;
    InterfaceAddition* interfaceAddition;
    UIElementEventHandler *uiElementEventHandler;
    int currentIndex = 0;
};

#endif // STANDARTTAB_H
