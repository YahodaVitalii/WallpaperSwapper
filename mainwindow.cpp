#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "style.h"
#include <QStyleOption>
#include <QDebug>
#include <QFontDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setInterfaceStyle();
   int fontId = QFontDatabase::addApplicationFont(":/resource/fonts/Inter-Regular.ttf");
   QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
   qDebug() << family;

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
  this->setStyleSheet(Style::getMainWindowStyle());
  ui->mainMenuStandartButton->setStyleSheet(Style::getMainMenuButtonsStyle());
  ui->mainMenuTimeButton->setStyleSheet(Style::getMainMenuButtonsStyle());
  ui->mainMenuMoodButton->setStyleSheet(Style::getMainMenuButtonsStyle());
  ui->mainMenuFutureButton->setStyleSheet(Style::getMainMenuButtonsStyle());
}

