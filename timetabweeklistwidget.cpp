#include "timetabweeklistwidget.h"
#include "ui_timetabweeklistwidget.h"

TimeTabWeekListWidget::TimeTabWeekListWidget(DBManager *dbManager, ImageManager *imageManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeTabWeekListWidget),dbManager(dbManager),imageManager(imageManager)
{
    ui->setupUi(this);
    interfaceAddition = new InterfaceAddition(this, dbManager, imageManager);
    interfaceAddition->CreateScrollArea(ui->CreateTab, interfaceAddition->getcontainerWidgetWeekImageListCreate(),600,300,0,40);
    interfaceAddition->CreateScrollArea(ui->ViewTab,interfaceAddition->getcontainerWidgetWeekImageListShow(),600,340,0,0);
    SetTimeTabWeekListWidgetStyle();
    CreateDialogWindowListOfImage();
    connect(interfaceAddition, &InterfaceAddition::setImageIntoWeekListItem, this, &TimeTabWeekListWidget::ShowDialogWindow);
    connect(interfaceAddition, &InterfaceAddition::weekImageListEditSignal, this, &TimeTabWeekListWidget::receiveWeekImageListEditSignal);
    currentImageIds = fillCurrentImageIds(days);

    currentWeekImageList = new WeekImageList();

    CreateTabViewListOfWidgets();
}

TimeTabWeekListWidget::~TimeTabWeekListWidget()
{
    delete ui;
}

void TimeTabWeekListWidget::SetTimeTabWeekListWidgetStyle()
{
    ui->TimeTabWeekListTabWidget->tabBar()->hide();
    ui->TimeTabWeekListTabWidget->setCurrentIndex(0);
    ui->CreateTab->setStyleSheet(Style::getCreateTabStyle());
}

void TimeTabWeekListWidget::CreateDialogWindowListOfImage()
{
    dialogWindowListOfImage = new DialogWindowListOfImage(this->dbManager,imageManager,interfaceAddition, this);
    connect(interfaceAddition, &InterfaceAddition::imageSelected, this, &TimeTabWeekListWidget::addImageInItem);
    dialogWindowListOfImage->setStyleSheet(Style::getTabsStyle());
}

void TimeTabWeekListWidget::CreateTabCreateListOfWidgets()
{
    for (const QString& day : days) {
        // Перевірка, чи ключ day існує у QMap currentImageIds
        if (currentImageIds.contains(day)) {
            interfaceAddition->CreateWeekListOfImageItem(currentImageIds[day], day);
        } else {
            // Якщо ключ не знайдено, вивести повідомлення про помилку або додати новий елемент
            qDebug() << "Key" << day << "not found in currentImageIds";
            interfaceAddition->CreateWeekListOfImageItem(-1, day);
        }
    }
}

void TimeTabWeekListWidget::CreateTabViewListOfWidgets()
{
    WeekImageLists = dbManager->getAllWeekImageLists();
    for (int i = 0; i < WeekImageLists.size(); i++)
    {
      qDebug()<<WeekImageLists[i].images["Other days"];
        interfaceAddition->CreateWeekListOfImageView(WeekImageLists[i].images["Other days"],WeekImageLists[i].getId(),WeekImageLists[i].getName());
      // qDebug()<< WeekImageLists[i].images["Other days"];
    }
   // qDebug()<<currentImageIds["Other days"];
}

void TimeTabWeekListWidget::AddNewWeekImageList()
{
    if (currentImageIds["Other days"] == -1) {
        // Loop through the days to find the first non -1 value
        for (const QString& day : days) {
            if (day != "Other days" && currentImageIds[day] != -1) {
                currentImageIds["Other days"] = currentImageIds[day];
                break;
            }
        }
    }
    currentWeekImageList = new WeekImageList(ui->lineEditNameWeekList->text(),currentImageIds);
    dbManager->insertWeekImageList(currentWeekImageList);
    interfaceAddition->CreateWeekListOfImageView(currentWeekImageList->images["Other days"],currentWeekImageList->getId(),currentWeekImageList->getName());
}

void TimeTabWeekListWidget::UpdateViewTabItem()
{
    currentWeekImageList->setName(ui->lineEditNameWeekList->text());
    currentWeekImageList->setImages(currentImageIds);
    dbManager->updateWeekImageList(currentWeekImageList);
}

QMap<QString, int> TimeTabWeekListWidget::fillCurrentImageIds(const QStringList &keys)
{
    QMap<QString, int> currentImageIds;
    for (const QString& key : keys) {
        currentImageIds[key] = -1;
    }
    return currentImageIds;
}

void TimeTabWeekListWidget::on_CreateTabButtonBox_accepted()
{
    ui->TimeTabWeekListTabWidget->setCurrentIndex(0);
    if (currentWeekImageList->getId() == -1){
    AddNewWeekImageList();
} else if (currentWeekImageList->getId() > 0)
    {
        UpdateViewTabItem();
        interfaceAddition->ClearConteinerWidget(interfaceAddition->getcontainerWidgetWeekImageListCreate());
        CreateTabViewListOfWidgets();

    }
}


void TimeTabWeekListWidget::on_CreateTabButtonBox_rejected()
{
    ui->TimeTabWeekListTabWidget->setCurrentIndex(0);
}

void TimeTabWeekListWidget::AddWeekListItem()
{
    currentImageIds = fillCurrentImageIds(days);
    interfaceAddition->ClearConteinerWidget(interfaceAddition->getcontainerWidgetWeekImageListCreate());
    CreateTabCreateListOfWidgets();
    ui->TimeTabWeekListTabWidget->setCurrentIndex(1);
}

void TimeTabWeekListWidget::ShowDialogWindow(QString day)
{
    dialogWindowListOfImage->show();
    currentDay = day;
}

void TimeTabWeekListWidget::addImageInItem(int index)
{
    // Перевірка, чи ключ currentDay існує у QMap currentImageIds
    if (currentImageIds.contains(currentDay)) {
        // Оновлення значення для ключа currentDay на значення index
        currentImageIds[currentDay] = index;
        qDebug() << "Updated image index for" << currentDay << "to" << index;
    } else {
        // Якщо ключ не знайдено, вивести повідомлення про помилку
        qDebug() << "Key" << currentDay << "not found in currentImageIds";
    }

    interfaceAddition->ClearConteinerWidget(interfaceAddition->getcontainerWidgetWeekImageListCreate());
    CreateTabCreateListOfWidgets();
    dialogWindowListOfImage->hide();
}

void TimeTabWeekListWidget::receiveWeekImageListEditSignal(int id)
{
    ui->TimeTabWeekListTabWidget->setCurrentIndex(1);
interfaceAddition->ClearConteinerWidget(interfaceAddition->getcontainerWidgetWeekImageListCreate());
currentWeekImageList = new WeekImageList(dbManager->findWeekImageListById(id));
ui->lineEditNameWeekList->setText(currentWeekImageList->getName());
currentImageIds = currentWeekImageList->getImages();
CreateTabCreateListOfWidgets();
}

