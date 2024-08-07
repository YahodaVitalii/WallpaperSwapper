#ifndef DIALOGWINDOWLISTOFIMAGE_H
#define DIALOGWINDOWLISTOFIMAGE_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QScrollArea>
#include <QVBoxLayout>
#include "sqlitedbmanager.h"
#include "style.h"
#include "imageslist.h"
#include "interfaceaddition.h"
#include "dbimagetablemanager.h"
namespace Ui {
class DialogWindowListOfImage;
}

class DialogWindowListOfImage : public QDialog
{
    Q_OBJECT
private:
    Ui::DialogWindowListOfImage *ui;
    DBManager* dbManager;
    ImageList* imageList;
    ImageLoader* imageLoader;
    InterfaceAddition* interfaceAddition;
    ScrollAreaManager* scrollAreaManager;

    QWidget *scrollAreaConterinerWidget;

public:
    explicit DialogWindowListOfImage(DBManager* dbManager,ImageList* imageList, InterfaceAddition* interfaceAddition,QWidget *parent = nullptr);

    ~DialogWindowListOfImage();
    void CreateListOfImageIntarface();
    void CreateListOfImageItem(int listItemCordinate_y, int index);
    void closeEvent();

private slots:
    void on_ListOfImageMenuBarPlusButton_clicked();

signals:
    void imageSelected(int index);
};

#endif // DIALOGWINDOWLISTOFIMAGE_H
