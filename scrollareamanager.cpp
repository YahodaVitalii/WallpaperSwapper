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
QWidget* ScrollAreaManager::getWidgetById(QWidget* parentWidget, int itemId, const char* propertyKey)
{
    // Отримуємо список всіх дочірніх віджетів від заданого контейнера
    const QList<QWidget*> widgets = parentWidget->findChildren<QWidget*>();
    // Проходимо через всі знайдені віджети і перевіряємо властивість "itemId"
    for (QWidget* widget : widgets) {
        if (widget->property(propertyKey).isValid() && widget->property(propertyKey).toInt() == itemId) {
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
void ScrollAreaManager::scrollToWidget(QWidget* parentWidget, QWidget* targetWidget)
{
    if (!parentWidget || !targetWidget) {
        qWarning() << "Parent widget or target widget is null!";
        return;
    }

    // Знаходимо QScrollArea як дочірній віджет
    QScrollArea* scrollArea = parentWidget->findChild<QScrollArea*>();
    if (!scrollArea) {
        qWarning() << "No QScrollArea found in parent widget!";
        return;
    }

    scrollArea->ensureWidgetVisible(targetWidget);
}

void ScrollAreaManager::scrollToWidgetById(QWidget* parentWidget, int itemId, const char* propertyKey)
{
    if (!parentWidget) {
        qWarning() << "Parent widget is null!";
        return;
    }

    // Знаходимо QScrollArea як дочірній віджет
    QScrollArea* scrollArea = parentWidget->findChild<QScrollArea*>();
    if (!scrollArea) {
        qWarning() << "No QScrollArea found in parent widget!1";
        return;
    }

    // Знаходимо цільовий віджет за ID
    QWidget* targetWidget = getWidgetById(parentWidget, itemId, propertyKey);
    if (targetWidget) {
        scrollArea->ensureWidgetVisible(targetWidget);
    } else {
        qWarning() << "Widget with ID" << itemId << "not found.";
    }
}
