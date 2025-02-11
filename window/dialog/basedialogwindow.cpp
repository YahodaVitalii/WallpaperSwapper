#include "basedialogwindow.h"

BaseDialogWindow::BaseDialogWindow(QWidget *parent, UIElementEventHandler *uiElementEventHandler)
    : QDialog(parent),uiElementEventHandler(uiElementEventHandler)
{
    scrollAreaManager = new ScrollAreaManager();
    interfaceAddition = new InterfaceAddition(this,uiElementEventHandler);
    initializeInterface();
}

BaseDialogWindow::~BaseDialogWindow()
{
delete scrollAreaManager;
delete interfaceAddition;
}

void BaseDialogWindow::initializeInterface()
{
this->setStyleSheet(Style::getTabsStyle());
}
