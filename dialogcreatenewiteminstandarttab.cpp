#include "dialogcreatenewiteminstandarttab.h"
#include "ui_dialogcreatenewiteminstandarttab.h"

DialogCreateNewItemInStandartTab::DialogCreateNewItemInStandartTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateNewItemInStandartTab)
{
    ui->setupUi(this);
}

DialogCreateNewItemInStandartTab::~DialogCreateNewItemInStandartTab()
{
    delete ui;
}
