#ifndef TIMETABWIDGETS_H
#define TIMETABWIDGETS_H
#include "baselistwidget.h"

class TimeTabWidgets : public BaseListWidget
{
public:
    explicit TimeTabWidgets(QWidget* parent = nullptr);
    ~TimeTabWidgets();
public slots:
    virtual void AcceptSavingOfList() = 0;
    void ReceiveEditSignalForListView(int id);
    void RejectSavingOfList();
    void  CreateViewListItem();

protected:
    virtual void PrepareTabForCreatingItem() =0;
    virtual void PrepareTabForEditingItem(int ListId) =0;
    virtual bool ValidateDataViewList();
    virtual  void BuildCreateTabInterface();

    QLineEdit* nameLineEdit;

    QTabWidget* tabWidget;
    QWidget* tabCreateList;
    QWidget *scrollAreaConterinerCreateTab;

private:
    void ConnectSignals() override;
   void BuildTabWidget();
};

#endif // TIMETABWIDGETS_H
