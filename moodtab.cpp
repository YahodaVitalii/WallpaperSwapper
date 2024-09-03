#include "moodtab.h"
#include "ui_moodtab.h"

MoodTab::MoodTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MoodTab)
{
    ui->setupUi(this);
}

MoodTab::~MoodTab()
{
    delete ui;
}
