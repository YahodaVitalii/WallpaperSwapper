#include "randomlistimageseditadd.h"
#include "ui_randomlistimageseditadd.h"

RandomListImagesEditAdd::RandomListImagesEditAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandomListImagesEditAdd)
{
    ui->setupUi(this);
}

RandomListImagesEditAdd::~RandomListImagesEditAdd()
{
    delete ui;
}
