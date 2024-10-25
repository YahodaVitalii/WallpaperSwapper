#include "scrollareamanager.h"

ScrollAreaManager::ScrollAreaManager(QWidget *parent)
    : QWidget{parent}
{

}
void ScrollAreaManager::CreateScrollArea(QWidget *parent, QWidget *child,const WidgetGeometry &geometry)
{

    QScrollArea* scrollArea = new QScrollArea(parent);
    scrollArea->setFixedSize(geometry.width, geometry.height);
    scrollArea->move(geometry.xPos, geometry.yPos);
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
QWidget* ScrollAreaManager::getWidgetById(QWidget* parentWidget, int itemId)
{
    // Отримуємо список всіх дочірніх віджетів від заданого контейнера
    const QList<QWidget*> widgets = parentWidget->findChildren<QWidget*>();
    // Проходимо через всі знайдені віджети і перевіряємо властивість "itemId"
    for (QWidget* widget : widgets) {
        if (widget->property("WidgetItemId").isValid() && widget->property("WidgetItemId").toInt() == itemId) {
            return widget;  // Повертаємо віджет, якщо ідентифікатор співпадає
        }
    }

    return nullptr;  // Якщо не знайдено, повертаємо nullptr
}

void ScrollAreaManager::initVBoxLayout(QWidget *containerWidget)
{
    QVBoxLayout *layoutCreateTab = new QVBoxLayout(containerWidget);
    containerWidget->setLayout(layoutCreateTab);
}
