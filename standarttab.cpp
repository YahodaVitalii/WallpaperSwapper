#include "standarttab.h"
#include "ui_standarttab.h"
#include "style.h"
StandartTab::StandartTab(DBManager *dbManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StandartTab), dbManager(dbManager)
{
    ui->setupUi(this);

    ui->StandartTabWidget->setStyleSheet(Style::getTabsStyle());
    ui->StandartTabButtonMenuWidget->setStyleSheet(Style::getStandartTabStyle());
    ui->StandartTabWlapperSliderWidget->setStyleSheet(Style::getStandartTabStyle());
    ui->SliderRightArrow->setIcon(QIcon(":/resource/SliderRightArrow.png"));
    ui->SliderRightArrow->setIconSize(QSize(65, 65));
    ui->SliderLeftArrow->setIcon(QIcon(":/resource/SliderLeftArrow.png"));
    ui->SliderLeftArrow->setIconSize(QSize(65, 65));

    images = dbManager->getAllImages();
    showImage(currentIndex);
}

StandartTab::~StandartTab()
{
    delete ui;
}

void StandartTab::showImage(int index)
{
    if (index >= 0 && index < images.size()) {
            QPixmap pixmap(images[index].getUrl());
            ui->SliderImage->setPixmap(pixmap.scaled(ui->SliderImage->size(), Qt::KeepAspectRatio));
    }
}

void StandartTab::nextImage()
{
    currentIndex = (currentIndex + 1) % images.size();
    showImage(currentIndex);
}

void StandartTab::previousImage()
{
currentIndex = (currentIndex - 1 + images.size()) % images.size();
    showImage(currentIndex);
}
void StandartTab::on_StandartTabChooseButton_clicked(){}
void StandartTab::on_StandartTabAddButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                   tr("Open Wlapper"), "/wlapper", tr("Image Files (*.png *.jpg *.bmp *.jpeg)"));

    qDebug() << "File selected:" << fileName;
    if (!fileName.isEmpty()) {
        QImage image(fileName);
        qDebug() << "Image loaded:" << !image.isNull() << ", Size:" << image.size();

        if (!image.isNull()) {
            auto wlapperImage = std::make_unique<WlapperImage>();
            wlapperImage->setName(QFileInfo(fileName).fileName());
            wlapperImage->setUrl(fileName);
            wlapperImage->setHeight(image.height());
            wlapperImage->setWidth(image.width());

            QPixmap pixmap(fileName);
            if (!pixmap.isNull()) {
                qDebug() << "Pixmap loaded successfully, Size:" << pixmap.size();
                ui->SliderImage->setPixmap(pixmap);
                ui->SliderImage->setScaledContents(true);
            } else {
                qDebug() << "Failed to load pixmap.";
            }

            if (!dbManager->insertIntoImageTable(*wlapperImage)) {
                qDebug() << "Error inserting data into the database.";
            }
        } else {
            QMessageBox::warning(this, tr("Loading Error"), tr("Could not load the image from the file."));
        }
    } else {
        qDebug() << "No file selected.";
    }
}


void StandartTab::on_SliderLeftArrow_clicked()
{
   previousImage();
}


void StandartTab::on_SliderRightArrow_clicked()
{
    nextImage();
}

bool StandartTab::setWallpaper(const QString &imagePath)
{
    std::wstring path = imagePath.toStdWString();

    BOOL result = SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, static_cast<void*>(const_cast<wchar_t*>(path.c_str())),
                                        SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);

    if (result) {
        return true;
    } else {
        qDebug() << "Failed to set wallpaper. Error:" << GetLastError();
        return false;
    }
}

void StandartTab::on_StandartTabSetButton_clicked()
{
    setWallpaper(images[currentIndex].getUrl());
}

