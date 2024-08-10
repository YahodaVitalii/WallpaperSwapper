#ifndef TABINTERFACEBUILDER_H
#define TABINTERFACEBUILDER_H
#include <qwidget.h>
#include "style.h"
#include <uielementfactory.h>

class TabInterfaceBuilder : public QWidget{
    Q_OBJECT

public:
    TabInterfaceBuilder(QWidget *parent, UIElementEventHandler *uiElementEventHandler);

    QTabWidget* CreateTabWidget(QWidget *conteinerWidget);
    QWidget* buildTabViewLists(QWidget *conteinerWidget, QWidget *scrollAreaConterinerViewTab);
    QWidget* buildTabCreateListForRandomList(QWidget *conteinerWidget, QWidget *scrollAreaConterinerCreateTab);
    QWidget* buildTabCreateListForWeekList(QWidget *conteinerWidget, QWidget *scrollAreaConterinerCreateTab);
    QWidget* buildTabCreateListForDayList(QWidget *conteinerWidget, QWidget *scrollAreaConterinerCreateTab);

    QLineEdit* CreateLineEdit(QWidget *containerWidget, const WidgetGeometry &geometry);
    QTimeEdit* CreateTimeEdit(QWidget *containerWidget, const WidgetGeometry &geometry);
    private:
    UIElementFactory* uiElementFactory;
    UIElementEventHandler *uiElementEventHandler;
    ScrollAreaManager scrollAreaManager;
};

#endif // TABINTERFACEBUILDER_H
