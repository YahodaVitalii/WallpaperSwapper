#ifndef DIALOGWINDOWCONTROLLER_H
#define DIALOGWINDOWCONTROLLER_H


#include "widgets/dialogwindowlistofimage.h"

class DialogWindowController
{
public:
    DialogWindowController(UIElementEventHandler *uiElementEventHandler);
    ~DialogWindowController();

    void Open(QWidget* parent);
    void Close();

private:
    DialogWindowListOfImage* dialogWindowListOfImage;
    UIElementEventHandler *uiElementEventHandler;
};

#endif // DIALOGWINDOWCONTROLLER_H
