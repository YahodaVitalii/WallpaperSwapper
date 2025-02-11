#include "window/dialog/windowchoosemood.h"
#include "ui_windowchoosemood.h"

WindowChoseMood::WindowChoseMood(QWidget *parent, UIElementEventHandler *uiElementEventHandler) :
    BaseDialogWindow(parent, uiElementEventHandler),
    ui(new Ui::WindowChoseMood)
{
    ui->setupUi(this);
}

WindowChoseMood::~WindowChoseMood()
{
    delete ui;
}
