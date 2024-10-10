 #include "weeklistwidget.h"
#include "ui_weeklistwidget.h"


WeekListWidget::WeekListWidget(QWidget *parent)
    : TimeTabWidgets(parent), ui(new Ui::WeekListWidget)
{
    ui->setupUi(this);

    connect(uiElementEventHandler, &UIElementEventHandler:: setImageIntoListItem, this, &WeekListWidget::ShowDialogWindowListOfImage);
    currentImageIds = fillCurrentImageIds();

    currentWeekImageList.reset(new WeekImageList());

    tabCreateList = tabInterfaceBuilder->buildTabCreateListForWeekList(tabWidget, scrollAreaConterinerCreateTab);
    tabWidget->addTab(tabCreateList, "Create List");

    nameLineEdit = tabInterfaceBuilder->CreateLineEdit(tabCreateList, WidgetGeometry(110, 30, 90, 10));
    CreateInterfaceViewTab();
}

WeekListWidget::~WeekListWidget()
{
    delete ui;
}

void WeekListWidget::CreatInterfaceCreateTab()
{
    for (int i = 0; i < static_cast<int>(DayOfWeek::Count); ++i) {
            DayOfWeek day = static_cast<DayOfWeek>(i);

            if (currentImageIds.contains(day)) {
                if (currentImageIds[day] != -1) {
                    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildWeekListItem(currentImageIds[day], day));
                } else {
                     scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerCreateTab, interfaceAddition->BuildWeekListItem(-1, day));
                }
            } else {
                qDebug() << "Key for" << dayOfWeekToString(day) << "not found in currentImageIds";
            }
        }
}


void WeekListWidget::CreateInterfaceViewTab()
{
    WeekImageLists = dbWeekListTableManager.getAllWeekImageLists();
    for (const auto& list : WeekImageLists) {
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildWeekListView(&list));
    }
}

void WeekListWidget::CreateViewTabItem()
{
    // Перевіряємо, чи значення для "OtherDays" встановлено на -1
    if (currentImageIds[DayOfWeek::OtherDays] == -1) {
        // Перебираємо всі дні, окрім "OtherDays"
        for (int i = static_cast<int>(DayOfWeek::Monday); i < static_cast<int>(DayOfWeek::Count); ++i) {
            DayOfWeek day = static_cast<DayOfWeek>(i);
            if (currentImageIds[day] != -1) {
                currentImageIds[DayOfWeek::OtherDays] = currentImageIds[day];
                break;
            }
        }
    }

    // Оновлюємо дані у списку зображень
    currentWeekImageList.reset(new WeekImageList(nameLineEdit->text(), currentImageIds));
    dbWeekListTableManager.insertWeekImageList(currentWeekImageList.data());
    scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, interfaceAddition->BuildWeekListView(currentWeekImageList.data()));
}
bool WeekListWidget::ValidateDataViewList()
{
        if (nameLineEdit->text().isEmpty()) {
            return false;
        }

        int validImageCount = 0;
        for (int value : currentImageIds.values()) {
            if (value != -1) {
                validImageCount++;
                if (validImageCount >= 2) {
                    return true;
                }
            }
        }

        return false;
}
void WeekListWidget::UpdateViewTabItem()
{
    currentWeekImageList->setName(nameLineEdit->text());
    currentWeekImageList->setImages(currentImageIds);
    dbWeekListTableManager.updateWeekImageList(currentWeekImageList.data());
}

void WeekListWidget::PrepareTabForEditingItem(int ListId)
{
    tabWidget->setCurrentIndex(1);
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    currentWeekImageList.reset(new WeekImageList(dbWeekListTableManager.findWeekImageListById(ListId)));
    nameLineEdit->setText(currentWeekImageList->getName());
    currentImageIds = currentWeekImageList->getImages();
    CreatInterfaceCreateTab();
}

void WeekListWidget::PrepareTabForCreatingItem()
{
    currentWeekImageList.reset(new WeekImageList());
    currentImageIds = fillCurrentImageIds();
    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CreatInterfaceCreateTab();
    nameLineEdit->clear();
    tabWidget->setCurrentIndex(1);
}

QMap<DayOfWeek, int> WeekListWidget::fillCurrentImageIds() {
    QMap<DayOfWeek, int> currentImageIds;
    for (int i = 0; i < static_cast<int>(DayOfWeek::Count); ++i) {
        currentImageIds[static_cast<DayOfWeek>(i)] = -1;
    }
    return currentImageIds;
}

void WeekListWidget::AcceptSavingOfList()
{
    if (ValidateDataViewList()) {
           int CurrentWeekListId = currentWeekImageList->getId();
           try {
               if (CurrentWeekListId == -1) {
                   CreateViewTabItem();
               } else if (CurrentWeekListId > 0) {
                   UpdateViewTabItem();
                   scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerViewTab);
                   CreateInterfaceViewTab();
               } else {
                   throw WSExceptions("Error: Week List has incorrect index: " + CurrentWeekListId);
               }
           } catch (const WSExceptions& e) {
               qDebug() << "Caught WSExceptions: " << e.what();
           }

           tabWidget->setCurrentIndex(0);
       } else {
           QMessageBox::warning(this, "Warning", "Before saving the list, please ensure that you have entered a name and added at least two images.");
       }
}
void WeekListWidget::ShowDialogWindowListOfImage(int itemId)
{
    dialogWindowController->Open(this);
    currentDay = static_cast<DayOfWeek>(itemId);
}

void WeekListWidget::addImageInList(int index)
{
    if (currentImageIds.contains(currentDay)) {
        currentImageIds[currentDay] = index;
       // qDebug() << "Updated image index for" << currentDay << "to" << index;
    } else {
        //qDebug() << "Key" << currentDay << "not found in currentImageIds";
    }

    scrollAreaManager->ClearScrollAreaConteinerWidget(scrollAreaConterinerCreateTab);
    CreatInterfaceCreateTab();
    dialogWindowController->Close();
}

