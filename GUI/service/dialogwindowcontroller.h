#ifndef DIALOGWINDOWCONTROLLER_H
#define DIALOGWINDOWCONTROLLER_H

#include "window/dialog/basedialogwindow.h"
#include "window/dialog/windowlistofimage.h"
#include "window/dialog/windowchoosemood.h"
#include "enums/dialogwindows.h"

class DialogWindowController
{
public:
    DialogWindowController( UIElementEventHandler *uiElementEventHandler);
    ~DialogWindowController();

    void Open(DialogWindows windowtype,QWidget* parent);
    void Close();

private:
    BaseDialogWindow *BuildWindow(DialogWindows type, QWidget* parent);

    BaseDialogWindow* dialogWindow;
    DialogWindowListOfImage* dialogWindowListOfImage;
    UIElementEventHandler *uiElementEventHandler;
    DialogWindows dialogWindows;
};

#endif // DIALOGWINDOWCONTROLLER_H
