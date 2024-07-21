#include "scrollareamanager.h"

ScrollAreaManager::ScrollAreaManager(QWidget *parent)
    : QWidget{parent}
{

}
void ScrollAreaManager::CreateScrollArea(QWidget *parent, QWidget *child,int width,int hight,int cordinate_X, int cordinate_Y)
{

    QScrollArea* scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(width, hight);
    scrollArea->move(cordinate_X, cordinate_Y);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(child);
}
void ScrollAreaManager::ClearScrollAreaConteinerWidget(QWidget *containerWidget)
{
    QLayoutItem *child;
    while ((child = containerWidget->layout()->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}
void ScrollAreaManager::setWidgetIntoScrollArea(QWidget* containerWidget, QWidget* childWidget) {
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(containerWidget->layout()); // на цьому рядку падає програма

    if (!layout) {
        layout = new QVBoxLayout(containerWidget);
    }

    layout->addWidget(childWidget);

}
