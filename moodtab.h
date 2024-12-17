#ifndef MOODTAB_H
#define MOODTAB_H

#include <QWidget>
#include "style.h"
#include "baselistwidget.h"
#include "emodjitablemanager.h"
#include "moodlisttablemeneger.h"
namespace Ui {
class MoodTab;
}

class MoodTab : public BaseListWidget
{
    Q_OBJECT

public:
    explicit MoodTab(QWidget *parent = nullptr);
    ~MoodTab();
    void CreateEmodjiPad();
    void PopulateEmodjiPad(QGridLayout* gridLayout, QWidget* emodjiPad);
public slots:
    void AddNewListItem(int index);
    void ShowDialogWindowListOfImage(int itemId);
private:
    Ui::MoodTab *ui;
    EmodjiTableManager* emodjiManager;

    void addImageInList(int index) override;
    void CreateInterfaceViewTab();
    QWidget* emodjiPad;
    QWidget* currentItemWidget = nullptr;
    QMap<int, QString> emodjis;
    QMap<int, int> currentImageIds;
    MoodListTableMeneger dbManager;
    QPair<int, int> moodImage;

    int currentEmodjiId;
    void ConnectSignals() override;
};

#endif // MOODTAB_H
