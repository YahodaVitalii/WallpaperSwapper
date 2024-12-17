#ifndef SCROLLAREAMANAGER_H
#define SCROLLAREAMANAGER_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include "widgetgeometry.h"

class ScrollAreaManager : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollAreaManager(QWidget *parent = nullptr);

    void CreateScrollArea(QWidget* parent, QWidget* child, const WidgetGeometry &geometry);
    void ClearScrollAreaConteinerWidget(QWidget* containerWidget);
    void setWidgetIntoScrollArea(QWidget* conteinerWidget,QWidget* childWidget);
    QWidget* getWidgetById(QWidget* parentWidget, int itemId, const char *propertyKey);
    void initVBoxLayout(QWidget* containerWidget);
    void scrollToWidget(QWidget* parentWidget, QWidget* targetWidget);
    void scrollToWidgetById(QWidget* parentWidget, int itemId, const char *propertyKey);
};

#endif // SCROLLAREAMANAGER_H
