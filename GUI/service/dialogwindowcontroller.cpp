#include "dialogwindowcontroller.h"

DialogWindowController::DialogWindowController(UIElementEventHandler *uiElementEventHandler)
    : dialogWindowListOfImage(nullptr),uiElementEventHandler(uiElementEventHandler) {}

DialogWindowController::~DialogWindowController()
{
    if (dialogWindow) {
        delete dialogWindow;
    }
}

void DialogWindowController::Open(DialogWindows windowtype, QWidget* parent)
{
    if (dialogWindow) {
        delete dialogWindow;
    }
    dialogWindow = BuildWindow(windowtype,parent);

    dialogWindow->show();
}

void DialogWindowController::Close()
{
    if (dialogWindow) {
        dialogWindow->hide();
        delete dialogWindow;
        dialogWindow = nullptr;
    }
}

BaseDialogWindow* DialogWindowController::BuildWindow(DialogWindows type, QWidget *parent)
{
    if(type == DialogWindows::ListOfWidget){
        return new DialogWindowListOfImage(parent, uiElementEventHandler);
    }
    if(type == DialogWindows::ChooseMood){
        return new WindowChoseMood(parent, uiElementEventHandler);
    }
    return nullptr;
}
