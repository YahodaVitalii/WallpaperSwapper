#ifndef UIELEMENTEVENTHANDLER_H
#define UIELEMENTEVENTHANDLER_H

#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include "imagelist.h"

class UIElementEventHandler : public QObject
{
    Q_OBJECT

public:
      UIElementEventHandler();

public slots:
    void on_buttonFullSize_clicked();
    void on_buttonImage_clicked();
    void on_buttonEdit_clicked();
    void on_ButtonSetImage_clicked();
    void on_ButtonAddImage_clicked();
    void on_EmojiButton_clicked();
    void onButtonBoxAccepted();
    void onButtonBoxRejected();

signals:
    void imageSelected(int imageIndex);
    void sendEditSignalToItem(int elementId);
    void setImageIntoListItem(int itemId);
    void sendEmodjiID(int id);
    void ButtonAddImageClicked();
    void ButtonBoxAccepted();
    void ButtonBoxRejected();

};


#endif // UIELEMENTEVENTHANDLER_H
