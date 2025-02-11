#ifndef BASEDIALOGWINDOW_H
#define BASEDIALOGWINDOW_H

#include <QDialog>
#include "DB/sqlitedbmanager.h"
#include "GUI/style/style.h"
#include "models/imagelist.h"
#include "GUI/CustomWidgets/interfaceaddition.h"
#include "DB/TablesManagers/imagetablemanager.h"

class BaseDialogWindow : public QDialog {
    Q_OBJECT
public:
    explicit BaseDialogWindow(QWidget *parent = nullptr, UIElementEventHandler *uiElementEventHandler = nullptr);
    virtual ~BaseDialogWindow();

    virtual void initializeInterface();
protected:
    ImageLoader* imageLoader;
    InterfaceAddition* interfaceAddition;
    ScrollAreaManager* scrollAreaManager;
    UIElementEventHandler *uiElementEventHandler;
};

#endif // BASEDIALOGWINDOW_H
