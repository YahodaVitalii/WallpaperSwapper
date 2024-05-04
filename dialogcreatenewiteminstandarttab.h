#ifndef DIALOGCREATENEWITEMINSTANDARTTAB_H
#define DIALOGCREATENEWITEMINSTANDARTTAB_H

#include <QDialog>

namespace Ui {
class DialogCreateNewItemInStandartTab;
}

class DialogCreateNewItemInStandartTab : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCreateNewItemInStandartTab(QWidget *parent = nullptr);
    ~DialogCreateNewItemInStandartTab();

private:
    Ui::DialogCreateNewItemInStandartTab *ui;
};

#endif // DIALOGCREATENEWITEMINSTANDARTTAB_H
