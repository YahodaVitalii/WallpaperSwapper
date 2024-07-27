#include "uielementfactory.h"

UIElementFactory::UIElementFactory(ImagesList *imagesList): imagesList(imagesList)
{

}

void UIElementFactory::CreateLableWithImage(QWidget *containerWidget, int imageIndex, const WidgetGeometry &geometry)
{
    QLabel* label = new QLabel(containerWidget);
    label->setFixedSize(geometry.width, geometry.height);
    label->move(geometry.xPos, geometry.yPos);
    if (imageIndex >= 0 && imageIndex < imagesList->getsizeOfImages()) // Check for valid index range
    {
        QPixmap pixmap(imagesList->GetImageByIndex(imageIndex).getUrl());
        label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio));
    }
    label->setScaledContents(true);
    label->show();
}

void UIElementFactory::CreateButtonInfo(QWidget *conteinerWidget)
{
    QPushButton* buttonInfo = new QPushButton(conteinerWidget);
    buttonInfo->setFixedSize(25, 25);
    buttonInfo->move(230, 55);
    buttonInfo-> setIcon(QIcon(":/resource/Info_light@3x.png"));
    buttonInfo->setIconSize(QSize(25, 25));
    buttonInfo->show();
    // connect(buttonInfo, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonInfo_clicked);
}

void UIElementFactory::CreateButtonDelete(QWidget *conteinerWidget, int index, int width, int hight, int cordinate_x, int cordinate_y)
{
    QPushButton* buttonDelete = new QPushButton(conteinerWidget);
    buttonDelete->setFixedSize(width, hight);
    buttonDelete->move(cordinate_x, cordinate_y);
    buttonDelete-> setIcon(QIcon(":/resource/Trash@3x.png"));
    buttonDelete->setIconSize(QSize(width, hight));
    buttonDelete->show();
    buttonDelete->setProperty("imageIndex", index);
    // connect(buttonDelete, &QPushButton::clicked, this, &DialogWindowListOfImage::on_buttonDelete_clicked);
}

void UIElementFactory::CreateButtonFullSize(QWidget *conteinerWidget, int index)
{
    QPushButton* buttonFullSize = new QPushButton(conteinerWidget);
    buttonFullSize->setFixedSize(25, 25);
    buttonFullSize->move(230, 20);
    buttonFullSize-> setIcon(QIcon(":/resource/Full@3x.png"));
    buttonFullSize->setIconSize(QSize(25, 25));
    buttonFullSize->show();
    buttonFullSize->setProperty("imageIndex", index);
    connect(buttonFullSize, &QPushButton::clicked, this, &UIElementFactory::on_buttonFullSize_clicked);
}

void UIElementFactory::CreateButtonImage(QWidget *conteinerWidget, int index, const WidgetGeometry &geometry)
{
    QPushButton* buttonImage = new QPushButton(conteinerWidget);
    buttonImage->setObjectName("buttonImage");  // Встановлення об'єктного імені
    buttonImage->setFixedSize(geometry.width, geometry.height);
    buttonImage->move(geometry.xPos, geometry.yPos);
    buttonImage->show();
    buttonImage->setProperty("imageIndex", index);
    connect(buttonImage, &QPushButton::clicked, this, &UIElementFactory::on_buttonImage_clicked);
}




void UIElementFactory::CreateLableWithText(QWidget *conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y)
{
    QLabel* labelText = new QLabel(conteinerWidget);
    labelText->setText(TextOfLabel);
    labelText->move(Cordinate_x,Cordinate_y);
    labelText->show();
}

void UIElementFactory::CreateToggleButton(QWidget *containerWidget, int id)
{
    QCheckBox* checkBox = new QCheckBox(containerWidget);
       //checkBox->setFixedSize(10, 10);
       checkBox->move(230, 10);
       checkBox->setProperty("CheckBoxId", id);
       checkBox->show();
       //connect(checkBox, &QCheckBox::stateChanged, this, &InterfaceAddition::on_checkBox_stateChanged);
}

void UIElementFactory::CreateButtonEdit(QWidget *conteinerWidget, int id, int width, int hight, int cordinate_x, int cordinate_y)
{
    QPushButton* buttonEdit = new QPushButton(conteinerWidget);
    buttonEdit->setFixedSize(width, hight);
    buttonEdit->move(cordinate_x, cordinate_y);
    buttonEdit-> setIcon(QIcon(":/resource/Edit_fill@3x.png"));
    buttonEdit->setIconSize(QSize(width, hight));
    buttonEdit->show();
    buttonEdit->setProperty("ListId", id);
    connect(buttonEdit, &QPushButton::clicked, this, &UIElementFactory::on_buttonEdit_clicked);
}

void UIElementFactory::CreateButtonSetImage(QWidget *conteinerWidget, QString day, const WidgetGeometry& geometry)
{
    QPushButton* ButtonSetImage = new QPushButton(conteinerWidget);
    ButtonSetImage->setObjectName("buttonImage");  // Встановлення об'єктного імені
    ButtonSetImage->setFixedSize(geometry.width, geometry.height);
    ButtonSetImage->move(geometry.xPos, geometry.yPos);
    ButtonSetImage-> setIcon(QIcon(":/resource/Img_load_box_fill@3x.png"));
    ButtonSetImage->setIconSize(QSize(40, 40));
    ButtonSetImage->show();
    ButtonSetImage->setProperty("DayOfButton", day);
    connect(ButtonSetImage, &QPushButton::clicked, this, &UIElementFactory::on_ButtonSetImage_clicked);
}

QTimeEdit* UIElementFactory::CreateTimeEditor(QWidget *conteinerWidget, int id, int cordinate_x, int cordinate_y)
{
    QTimeEdit* TimeEdit = new QTimeEdit(conteinerWidget);
    TimeEdit->setFixedSize(70,30);
    TimeEdit->move(cordinate_x, cordinate_y);
    TimeEdit->setProperty("id",id);
    TimeEdit->show();
    return TimeEdit;
}
void UIElementFactory::on_buttonFullSize_clicked()
{
    QString imageUrl = imagesList->GetImageByIndex(sender()->property("imageIndex").toInt()).getUrl();
    QDesktopServices::openUrl(QUrl("file:///" + imageUrl));
}

void UIElementFactory::on_buttonImage_clicked() {
    int index = sender()->property("imageIndex").toInt();
    emit imageSelected(index);  // Сигнал передає індекс зображення
}

void UIElementFactory::on_buttonEdit_clicked()
{
    int elementId = sender()->property("ListId").toInt();
    emit sendEditSignalToItem(elementId);
}

void UIElementFactory::on_ButtonSetImage_clicked()
{
    QString day = sender()->property("DayOfButton").toString();
    emit setImageIntoWeekListItem(day);  // Сигнал передає індекс зображення
}
