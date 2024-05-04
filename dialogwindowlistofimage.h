#ifndef DIALOGWINDOWLISTOFIMAGE_H
#define DIALOGWINDOWLISTOFIMAGE_H

#include <QDialog>
#include <QDesktopServices>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QScrollArea>
#include <QVBoxLayout>
#include "sqlitedbmanager.h"
#include "style.h"
#include "imagemanager.h"
namespace Ui {
class DialogWindowListOfImage;
}

class DialogWindowListOfImage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogWindowListOfImage(DBManager* dbManager,QWidget *parent = nullptr);

    ~DialogWindowListOfImage();
    void CreateListOfImageIntarface();
    void CreateListOfImageItem(int listItemCordinate_y, int index);

private slots:
    void on_ListOfImageMenuBarPlusButton_clicked();
    void on_buttonFullSize_clicked();
    void on_buttonInfo_clicked();
     void on_buttonDelete_clicked();
    void on_buttonImage_clicked();

signals:
     void imageSelected(int index);
private:
    Ui::DialogWindowListOfImage *ui;
    DBManager* dbManager;
    ImageManager* imageManager;

   int listItemCordinate_y;
     QScrollArea* scrollArea =new QScrollArea(this);
     QWidget *containerWidget = new QWidget();
};

#endif // DIALOGWINDOWLISTOFIMAGE_H
