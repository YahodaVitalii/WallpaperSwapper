#include "dialogwindowcontroller.h"

DialogWindowController::DialogWindowController(UIElementEventHandler *uiElementEventHandler)
    : dialogWindowListOfImage(nullptr),uiElementEventHandler(uiElementEventHandler) // Ініціалізуємо вказівник як nullptr
{
}

DialogWindowController::~DialogWindowController()
{
    // Якщо діалогове вікно існує, видаляємо його
    if (dialogWindowListOfImage) {
        delete dialogWindowListOfImage;
    }
}

void DialogWindowController::Open(QWidget* parent)
{
    // Створюємо діалогове вікно тільки якщо воно не існує
    if (dialogWindowListOfImage) {
        delete dialogWindowListOfImage;
    }
    dialogWindowListOfImage = new DialogWindowListOfImage(parent,uiElementEventHandler);
    dialogWindowListOfImage->show();
}

void DialogWindowController::Close()
{
    if (dialogWindowListOfImage) {
        dialogWindowListOfImage->hide();
        delete dialogWindowListOfImage;
        dialogWindowListOfImage = nullptr; // Обнуляємо вказівник після видалення
    }
}
