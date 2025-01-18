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
#include "GUI/style/style.h"
#include "imagelist.h"
#include "GUI/CustomWidgets/interfaceaddition.h"
#include "imagetablemanager.h"
namespace Ui {
class DialogWindowListOfImage;
}

class DialogWindowListOfImage : public QDialog
{
    Q_OBJECT
private:
    Ui::DialogWindowListOfImage *ui;
    ImageList* imageList;
    ImageLoader* imageLoader;
    InterfaceAddition* interfaceAddition;
    ScrollAreaManager* scrollAreaManager;
    UIElementEventHandler *uiElementEventHandler;

    QWidget *scrollAreaConterinerWidget;

public:
    explicit DialogWindowListOfImage(QWidget *parent = nullptr, UIElementEventHandler *uiElementEventHandler = nullptr);

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
