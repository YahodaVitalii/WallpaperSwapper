#include "uielementeventhandler.h"


UIElementEventHandler::UIElementEventHandler() {}


void UIElementEventHandler::on_buttonFullSize_clicked()
{
    QString imageUrl = sender()->property("imagePath").toString();
    QDesktopServices::openUrl(QUrl("file:///" + imageUrl));
}

void UIElementEventHandler::on_buttonImage_clicked() {
    int index = sender()->property("imageIndex").toInt();
    emit imageSelected(index);
}

void UIElementEventHandler::on_buttonEdit_clicked()
{
    int elementId = sender()->property("ListId").toInt();
    emit sendEditSignalToItem(elementId);
}

void UIElementEventHandler::on_ButtonSetImage_clicked()
{
    QString day = sender()->property("DayOfButton").toString();
    emit setImageIntoWeekListItem(day);
}

void UIElementEventHandler::on_ButtonAddImage_clicked()
{
    emit ButtonAddImageClicked();
}

void UIElementEventHandler::onButtonBoxAccepted()
{
    emit ButtonBoxAccepted();
}

void UIElementEventHandler::onButtonBoxRejected()
{
    emit ButtonBoxRejected();
}
