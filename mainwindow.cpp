#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "style.h"
#include <QStyleOption>
#include <QDebug>
#include <QFontDatabase>
MainWindow::MainWindow(DBManager* dbManager,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), dbManager(dbManager)
{
    ui->setupUi(this);

    setInterfaceStyle();
    imageList = SQLTableImageList::getInstance();

    standartTab = new StandartTab(dbManager,imageList,this);
    standartTab ->move(165, 0);
    standartTab->setFixedSize(640,500);
    standartTab->hide();


    timeTab = new TimeTab(this);
    timeTab->move(165, 0);
    timeTab->setFixedSize(640,500);
    timeTab->hide();


    moodTab = new MoodTab(this);
    moodTab->move(165, 0);
    moodTab->setFixedSize(640,500);
    moodTab->setStyleSheet(Style::getTabsStyle());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::PaintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}


void MainWindow::setInterfaceStyle()
{
    int fontId = QFontDatabase::addApplicationFont(":/resource/fonts/Inter-Regular.ttf");
    QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);

    this->setStyleSheet(Style::getMainWindowStyle());
    ui->mainMenuStandartButton->setStyleSheet(Style::getMainMenuButtonsStyle());
    ui->mainMenuTimeButton->setStyleSheet(Style::getMainMenuButtonsStyle());
    ui->mainMenuMoodButton->setStyleSheet(Style::getMainMenuButtonsStyle());
    ui->mainMenuFutureButton->setStyleSheet(Style::getMainMenuButtonsStyle());

}


void MainWindow::on_mainMenuStandartButton_clicked()
{
    standartTab ->show();
    timeTab->hide();
    moodTab->hide();
}


void MainWindow::on_mainMenuTimeButton_clicked()
{
    timeTab->show();
    standartTab ->hide();
    moodTab->hide();
}


void MainWindow::on_mainMenuMoodButton_clicked()
{
    timeTab->hide();
    standartTab ->hide();
    moodTab->show();
}

