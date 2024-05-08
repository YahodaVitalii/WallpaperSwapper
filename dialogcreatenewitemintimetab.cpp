#include "dialogcreatenewitemintimetab.h"
#include "ui_dialogcreatenewitemintimetab.h"

DialogCreateNewItemInTimeTab::DialogCreateNewItemInTimeTab(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogCreateNewItemInTimeTab)
{
    ui->setupUi(this);
}

DialogCreateNewItemInTimeTab::~DialogCreateNewItemInTimeTab()
{
    delete ui;
}
