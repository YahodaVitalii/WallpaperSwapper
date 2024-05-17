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
    void CreateRandomListOfImageItem(int index);
    void CreateRandomListOfImageView(int index,int id,QString name,QString time);

    void CreateLableWithImage(QWidget* listItemMeinWidget, int index, int cordinate_x, int cordinate_y);
    void CreateButtonInfo(QWidget* listItemMeinWidget);
    void CreateButtonDelete(QWidget* listItemMeinWidget, int index, int width, int hight, int cordinate_x, int cordinate_y);
    void CreateButtonFullSize(QWidget* listItemMeinWidget, int index);
    void CreateButtonImage(QWidget* listItemMeinWidget,int index);
    void setWidgetIntoScrollArea(QWidget* conteinerWidget,QWidget* childWidget);
    void CreateButtonTurnOnTurnOff(QWidget* conteinerWidget);
    void CreateLableWithText(QWidget* conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y);
    void CreateButtonEdit(QWidget* conteinerWidget, int id, int width, int hight, int cordinate_x, int cordinate_y);

    QWidget* getContainerWidgetDWindowImageOfList() const;
    void CreateContainerWidgetDWindowImageOfList();
    void DeleteContainerWidgetDWindowImageOfList();
    QWidget* getContainerWidgetRandomImageListCreate() const;
    QWidget *getcontainerWidgetRandomImageListShow() const;

   void CreateScrollArea(QWidget* parent, QWidget* child, int width, int hight, int cordinate_X, int cordinate_Y);
    void ClearConteinerWidget(QWidget* containerWidget);

    //void setTargetContainer(QWidget *container);


signals:
    void imageSelected(int index);
    void randomImageListEditSignal(int id);
private slots:
    void on_buttonFullSize_clicked();
    void on_buttonImage_clicked();
   void on_buttonEdit_clicked();
private:
    QWidget *containerWidgetDWindowImageOfList = nullptr;
    QWidget *containerWidgetRandomImageListCreate = nullptr;
    QWidget *containerWidgetRandomImageListShow = nullptr;

    QWidget *parentWidget;
    ImageManager* imageManager;
    DBManager* dbManager;

};

#endif // INTERFACEADDITION_H
