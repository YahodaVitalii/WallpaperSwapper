#include "moodtab.h"
#include "ui_moodtab.h"

MoodTab::MoodTab(QWidget *parent)
    : BaseListWidget(parent),
    ui(new Ui::MoodTab)
{
    ui->setupUi(this);
emodjiManager = new EmodjiTableManager();

 ui->MoodTabWidget->setStyleSheet(Style::getTabsStyle());
CreateEmodjiPad();

  tabViewLists = buildTabViewLists(ui->MoodTabWidget,scrollAreaConterinerViewTab,WidgetGeometry( 350, 400, 20, 25));
  tabViewLists ->setStyleSheet(Style::getMoodTabStyle());

   ConnectSignals();

CreateInterfaceViewTab();
}

MoodTab::~MoodTab()
{
    delete ui;
}

void MoodTab::CreateEmodjiPad()
{
    emodjiPad = new QWidget(ui->MoodTabWidget);
    emodjiPad->setStyleSheet(Style::getMoodTabStyle());

    QGridLayout *gridLayout = new QGridLayout(emodjiPad);
    emodjiPad->setLayout(gridLayout);

    // Викликаємо окрему функцію для заповнення сітки емоджі
    PopulateEmodjiPad(gridLayout, emodjiPad);

    // Додаємо скрол для перегляду емоджі
    scrollAreaManager->CreateScrollArea(ui->MoodTabWidget, emodjiPad, WidgetGeometry(180, 450, 440, 25));
}

void MoodTab::PopulateEmodjiPad(QGridLayout* gridLayout, QWidget* emodjiPad)
{
     emodjis = emodjiManager->getAllRecords();
          // Створюємо екземпляр InterfaceAddition для використання

        int row = 0;
        int column = 0;

        for (auto it = emodjis.begin(); it != emodjis.end(); ++it) {
            QPushButton *emojiButton = interfaceAddition->CreateEmojiButton(it.key(),it.value(), emodjiPad);

            gridLayout->addWidget(emojiButton, row, column);

            column++;
            if (column == 4) {
                column = 0;
                row++;
            }
        }
}

void MoodTab::AddNewListItem(int index)
{
    if(currentImageIds.contains(index)){
    qDebug()<<"not exist";
    }else{
        currentItemWidget  = interfaceAddition->BuildMoodTabItem(index,-1);
        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab, currentItemWidget);
    }
}

void MoodTab::ShowDialogWindowListOfImage(int itemId)
{
   currentItemWidget = scrollAreaManager->getWidgetById(scrollAreaConterinerViewTab,itemId);
      currentEmodjiId = itemId;
    dialogWindowController->Open(this);

}
void MoodTab::addImageInList(int index)
{
    if (currentItemWidget) {
           // Оновлюємо зображення в поточному елементі MoodTabItem
           QLabel* label = currentItemWidget->findChild<QLabel*>("imageLabel"); // Припустимо, що у QLabel є ім'я "imageLabel"
           if (label) {
               QPixmap pixmap(imageList->GetImageByIndex(index).getUrl());
               label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
           }
       }
    if (currentImageIds.contains(currentEmodjiId)) {
            // Якщо такий ключ вже є, оновлюємо значення
            currentImageIds[currentEmodjiId] = index;
            dbManager.updateList(QPair<int, int>(currentEmodjiId, index)); // Припускаємо, що є метод для оновлення запису в БД
        } else {
            // Якщо немає такого ключа, додаємо новий запис
            currentImageIds.insert(currentEmodjiId, index);
            dbManager.insertIntoTable(QPair<int, int>(currentEmodjiId, index));
        }

       dialogWindowController->Close();
}

void MoodTab::CreateInterfaceViewTab()
{
    currentImageIds = dbManager.getAllRecords();
    for (auto it = currentImageIds.constBegin(); it != currentImageIds.constEnd(); ++it) {
        int emodjiId = it.key();
        int imageId = it.value();

        qDebug() << "Emodji ID:" << emodjiId << "Image ID:" << imageId;

        scrollAreaManager->setWidgetIntoScrollArea(scrollAreaConterinerViewTab,
                                                   interfaceAddition->BuildMoodTabItem(emodjiId, imageId));
    }
}

void MoodTab::ConnectSignals()
{
     BaseListWidget::ConnectSignals();
     connect(uiElementEventHandler, &UIElementEventHandler::sendEmodjiID, this, &MoodTab::AddNewListItem);
     connect(uiElementEventHandler, &UIElementEventHandler::setImageIntoListItem, this, &MoodTab::ShowDialogWindowListOfImage);
}
