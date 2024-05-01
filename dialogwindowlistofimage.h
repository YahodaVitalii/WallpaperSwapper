#ifndef DIALOGWINDOWLISTOFIMAGE_H
#define DIALOGWINDOWLISTOFIMAGE_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include "sqlitedbmanager.h"
#include "style.h"
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
    void CreateListOfImageItem(QString path);

private slots:
    void on_ListOfImageMenuBarPlusButton_clicked();

private:
    Ui::DialogWindowListOfImage *ui;
    DBManager* dbManager;
};

#endif // DIALOGWINDOWLISTOFIMAGE_H
