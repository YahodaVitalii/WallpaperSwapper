#ifndef SCROLLAREAMANAGER_H
#define SCROLLAREAMANAGER_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>

class ScrollAreaManager : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollAreaManager(QWidget *parent = nullptr);

    void CreateScrollArea(QWidget* parent, QWidget* child, int width, int hight, int cordinate_X, int cordinate_Y);
    void ClearScrollAreaConteinerWidget(QWidget* containerWidget);
    void setWidgetIntoScrollArea(QWidget* conteinerWidget,QWidget* childWidget);

};

#endif // SCROLLAREAMANAGER_H
