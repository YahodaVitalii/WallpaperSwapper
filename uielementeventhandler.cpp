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
    int itemId = sender()->property("ItemId").toInt();
    emit setImageIntoListItem(itemId);
}

void UIElementEventHandler::on_ButtonAddImage_clicked()
{
    emit ButtonAddImageClicked();
}

void UIElementEventHandler::on_EmojiButton_clicked()
{
    int key = sender()->property("emojiKey").toInt();
    emit sendEmodjiID(key);
}

void UIElementEventHandler::onButtonBoxAccepted()
{
    qDebug() << "Accepted signal received";
    emit ButtonBoxAccepted();
}

void UIElementEventHandler::onButtonBoxRejected()
{
    emit ButtonBoxRejected();
}

void UIElementEventHandler::on_checkBox_stateChanged()
{

    QVariant property = sender()->property("ImageList");
    BaseImageList* imageList = static_cast<BaseImageList*>(property.value<void*>());

    emit sendList(imageList);
}
