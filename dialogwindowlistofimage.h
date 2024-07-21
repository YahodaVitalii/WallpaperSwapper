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
namespace Ui {
class DialogWindowListOfImage;
}

class DialogWindowListOfImage : public QDialog
{
    Q_OBJECT
private:
    Ui::DialogWindowListOfImage *ui;
    DBManager* dbManager;
    ImagesList* imageManager;
    ImageLoader* imageLoader;
    InterfaceAddition* interfaceAddition;
    ScrollAreaManager* scrollAreaManager;

    QWidget *scrollAreaConterinerWidget;
public:
    explicit DialogWindowListOfImage(DBManager* dbManager,ImagesList* imageManager, InterfaceAddition* interfaceAddition,QWidget *parent = nullptr);

    ~DialogWindowListOfImage();
    void CreateListOfImageIntarface();
    void CreateListOfImageItem(int listItemCordinate_y, int index);
    void closeEvent();
    void showDialogWindow();

private slots:
    void on_ListOfImageMenuBarPlusButton_clicked();
    //    void on_buttonFullSize_clicked();
    //    void on_buttonInfo_clicked();
    //    void on_buttonDelete_clicked();
    //    void on_buttonImage_clicked();

signals:
    void imageSelected(int index);
};

#endif // DIALOGWINDOWLISTOFIMAGE_H
