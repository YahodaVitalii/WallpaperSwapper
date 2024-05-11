#ifndef INTERFACEADDITION_H
#define INTERFACEADDITION_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QVBoxLayout>
#include <QDebug>
#include <QDesktopServices>
#include <QScrollArea>
#include "style.h"
#include "imagemanager.h"
#include "sqlitedbmanager.h"
class InterfaceAddition : public QWidget{
    Q_OBJECT
public:
    InterfaceAddition(QWidget *parent, DBManager* dbManageer, ImageManager* imageManager);
    ~InterfaceAddition();
    void CreateListOfImageItem(int index);
    void CreateLableWithImage(QWidget* listItemMeinWidget,int index);
    void CreateButtonInfo(QWidget* listItemMeinWidget);
    void CreateButtonDelete(QWidget* listItemMeinWidget,int index);
    void CreateButtonFullSize(QWidget* listItemMeinWidget, int index);
    void CreateButtonImage(QWidget* listItemMeinWidget,int index);
    void setWidgetIntoScrollArea(QWidget* conteinerWidget,QWidget* childWidget);
    void CreateRandomListOfImageItem(int index);
    QWidget* getContainerWidgetDWindowImageOfList() const;
    void CreateContainerWidgetDWindowImageOfList();
    void DeleteContainerWidgetDWindowImageOfList();
    QWidget* getContainerWidgetRandomImageListCreate() const;
   void CreateScrollArea(QWidget* parent, QWidget* child, int width, int hight, int cordinate_X, int cordinate_Y);
    void ClearConteinerWidget(QWidget* containerWidget);

    //void setTargetContainer(QWidget *container);


signals:
    void imageSelected(int index);
private slots:
    void on_buttonFullSize_clicked();
    void on_buttonImage_clicked();
private:
    QWidget *containerWidgetDWindowImageOfList = nullptr;
    QWidget *containerWidgetRandomImageListCreate = nullptr;

    QWidget *parentWidget;
    ImageManager* imageManager;
    DBManager* dbManager;

};

#endif // INTERFACEADDITION_H
