#include "moodtab.h"
#include "ui_moodtab.h"

MoodTab::MoodTab(QWidget *parent)
    : BaseListWidget(parent),
      ui(new Ui::MoodTab)
{
    ui->setupUi(this);
    emodjiManager = new EmodjiTableManager();

    CreateEmodjiPad();
    tabViewLists = buildTabViewLists(ui->MoodTabWidget,scrollAreaConterinerViewTab,WidgetGeometry( 350, 400, 20, 25));
    tabViewLists ->setStyleSheet(Style::getMoodTabStyle());
    ui->MoodTabWidget->setStyleSheet(Style::getTabsStyle());

    ConnectSignals();

    CreateInterfaceViewTab();

     dialogWindowController->Open(DialogWindows::ChooseMood, this);
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

    PopulateEmodjiPad(gridLayout, emodjiPad);

    scrollAreaManager->CreateScrollArea(ui->MoodTabWidget, emodjiPad, WidgetGeometry(180, 450, 440, 25));
}

void MoodTab::PopulateEmodjiPad(QGridLayout* gridLayout, QWidget* emodjiPad)
{
    emodjis = emodjiManager->getAllRecords();

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
    currentItemWidget = scrollAreaManager->getWidgetById(scrollAreaConterinerViewTab,itemId,"WidgetItemId");
    currentEmodjiId = itemId;
    dialogWindowController->Open(DialogWindows::ListOfWidget, this);

}
void MoodTab::addImageInList(int index)
{
    if (currentItemWidget) {
        QLabel* label = currentItemWidget->findChild<QLabel*>("imageLabel"); // Припустимо, що у QLabel є ім'я "imageLabel"
        if (label) {
            QPixmap pixmap(imageList->GetImageByIndex(index).getUrl());
            label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
        }
    }
    if (currentImageIds.contains(currentEmodjiId)) {
        currentImageIds[currentEmodjiId] = index;
        dbManager.updateList(QPair<int, int>(currentEmodjiId, index)); // Припускаємо, що є метод для оновлення запису в БД
    } else {
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
    connect(uiElementEventHandler, &UIElementEventHandler::sendEmodjiID, this, &MoodTab::AddNewListItem);
    connect(uiElementEventHandler, &UIElementEventHandler::setImageIntoListItem, this, &MoodTab::ShowDialogWindowListOfImage);
}
