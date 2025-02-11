#ifndef WINDOWCHOOSEMOOD_H
#define WINDOWCHOOSEMOOD_H

#include <QDialog>
#include "basedialogwindow.h"

namespace Ui {
class WindowChoseMood;
}

class WindowChoseMood : public BaseDialogWindow
{
    Q_OBJECT

public:
    explicit WindowChoseMood(QWidget *parent = nullptr, UIElementEventHandler *uiElementEventHandler= nullptr);
    //make uiElementEventHandler not a default parameter
    ~WindowChoseMood();

private:
    Ui::WindowChoseMood *ui;
};

#endif // WINDOWCHOOSEMOOD_H
