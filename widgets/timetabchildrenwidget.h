#ifndef TIMETABCHILDRENWIDGET_H
#define TIMETABCHILDRENWIDGET_H
#include "baselistwidget.h"

class TimeTabChildrenWidget : public BaseListWidget
{
Q_OBJECT
public:
    explicit TimeTabChildrenWidget(QWidget* parent = nullptr);
    ~TimeTabChildrenWidget();
public slots:
    virtual void AcceptSavingOfList() = 0;
    void ReceiveEditSignalForListView(int id);
    void RejectSavingOfList();
    void  CreateViewListItem();
    void ResendList(BaseImageList* imageList);
signals:
    void resendListSignal(BaseImageList* imageList);

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
    virtual void ConnectSignals() override;
    void BuildTabWidget();
};

#endif // TIMETABCHILDRENWIDGET_H
