#ifndef INTERFACEADDITION_H
#define INTERFACEADDITION_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QDebug>
#include <QDesktopServices>
#include "style.h"
#include "imagemanager.h"
#include "sqlitedbmanager.h"
class InterfaceAddition : public QWidget{
    Q_OBJECT
public:
    InterfaceAddition(QWidget *parent, DBManager* dbManageer, ImageManager* imageManager);
 void CreateListOfImageItem(int index);
 void CreateLableWithImage(QWidget* listItemMeinWidget,int index);
 void CreateButtonInfo(QWidget* listItemMeinWidget);
 void CreateButtonDelete(QWidget* listItemMeinWidget,int index);
 void CreateButtonFullSize(QWidget* listItemMeinWidget, int index);
 void CreateButtonImage(QWidget* listItemMeinWidget,int index);
 QWidget *containerWidget = new QWidget();


private slots:
 void on_buttonFullSize_clicked();
private:
    QWidget *parentWidget;
    ImageManager* imageManager;
    DBManager* dbManager;

};

#endif // INTERFACEADDITION_H
