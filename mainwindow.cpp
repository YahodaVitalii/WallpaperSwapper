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
    uiElementFactory = new UIElementFactory(imageList);
    interfaceAddition = new InterfaceAddition(this,uiElementFactory);
    dialogWindowListOfImage = new DialogWindowListOfImage(dbManager,imageList,interfaceAddition,this);

    standartTab = new StandartTab(dbManager,imageList,dialogWindowListOfImage,this);
    standartTab ->move(165, 0);

    timeTab = new TimeTab(dbManager,imageList,dialogWindowListOfImage,this);
    timeTab->move(165, 0);

    connect(uiElementFactory, &UIElementFactory::imageSelected, standartTab, &StandartTab::updateImage);
    connect(uiElementFactory, &UIElementFactory::imageSelected, timeTab->getTimeTabRandomListWidget(), &TimeTabRandomListWidget::addImageInList);
    connect(uiElementFactory, &UIElementFactory::imageSelected, timeTab->getTimeTabWeekListWidget(), &TimeTabWeekListWidget::addImageInList);
    connect(uiElementFactory, &UIElementFactory::imageSelected, timeTab->getTimeTabDayListWidget(), &TimeTabDayListWidget::addImageInList);
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
}


void MainWindow::on_mainMenuTimeButton_clicked()
{
    timeTab->show();
    standartTab ->hide();
}

