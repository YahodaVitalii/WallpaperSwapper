#ifndef WINDOWLISTOFIMAGE_H
#define WINDOWLISTOFIMAGE_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>
#include <QScrollArea>
#include <QVBoxLayout>
#include "DB/sqlitedbmanager.h"
#include "GUI/style/style.h"
#include "models/imagelist.h"
#include "GUI/CustomWidgets/interfaceaddition.h"
#include "DB/TablesManagers/imagetablemanager.h"
#include "basedialogwindow.h"
namespace Ui {
class DialogWindowListOfImage;
}

class DialogWindowListOfImage : public BaseDialogWindow
{
    Q_OBJECT
private:
    Ui::DialogWindowListOfImage *ui;
    ImageList* imageList;
    ImageLoader* imageLoader;

    QWidget *scrollAreaConterinerWidget;

public:
    explicit DialogWindowListOfImage(QWidget *parent = nullptr, UIElementEventHandler *uiElementEventHandler = nullptr);

    ~DialogWindowListOfImage();
    void CreateListOfImageIntarface();
    void CreateListOfImageItem(int listItemCordinate_y, int index);
    void initializeInterface() override;

private slots:
    void on_ListOfImageMenuBarPlusButton_clicked();

signals:
    void imageSelected(int index);
};

#endif // WINDOWLISTOFIMAGE_H
