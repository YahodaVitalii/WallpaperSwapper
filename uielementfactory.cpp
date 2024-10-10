#include "uielementfactory.h"

UIElementFactory::UIElementFactory(UIElementEventHandler *uiElementEventHandler): uiElementEventHandler(uiElementEventHandler)
{
    imageList = SQLTableImageList::getInstance();
}

UIElementFactory::UIElementFactory()
{
imageList = SQLTableImageList::getInstance();
uiElementEventHandler = new UIElementEventHandler();
}

void UIElementFactory::CreateLableWithImage(QWidget *containerWidget, int imageIndex, const WidgetGeometry &geometry)
{
    QLabel* label = new QLabel(containerWidget);
     label->setObjectName("imageLabel");
    label->setFixedSize(geometry.width, geometry.height);
    label->move(geometry.xPos, geometry.yPos);


    if (imageIndex >= 0 && imageIndex < imageList->getsizeOfImages()) // Check for valid index range
    {
        QPixmap pixmap(imageList->GetImageByIndex(imageIndex).getUrl());
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
    QString imageUrl = imageList->GetImageByIndex(index).getUrl();
    buttonFullSize->setProperty("imagePath", imageUrl);
    connect(buttonFullSize, &QPushButton::clicked, uiElementEventHandler, &UIElementEventHandler::on_buttonFullSize_clicked);
}

void UIElementFactory::CreateButtonImage(QWidget *conteinerWidget, int index, const WidgetGeometry &geometry)
{
    QPushButton* buttonImage = new QPushButton(conteinerWidget);
    buttonImage->setObjectName("buttonImage");  // Встановлення об'єктного імені
    buttonImage->setFixedSize(geometry.width, geometry.height);
    buttonImage->move(geometry.xPos, geometry.yPos);
    buttonImage->show();
    buttonImage->setProperty("imageIndex", index);
    connect(buttonImage, &QPushButton::clicked, uiElementEventHandler, &UIElementEventHandler::on_buttonImage_clicked);
}

QLabel* UIElementFactory::CreateLableWithText(QWidget *conteinerWidget, QString TextOfLabel, int Cordinate_x, int Cordinate_y)
{
    QLabel* labelText = new QLabel(conteinerWidget);
    labelText->setText(TextOfLabel);
    labelText->move(Cordinate_x,Cordinate_y);
    labelText->show();
    return labelText;
}

void UIElementFactory::CreateToggleButton(QWidget *containerWidget, int id)
{
    QCheckBox* checkBox = new QCheckBox(containerWidget);
       //checkBox->setFixedSize(10, 10);
       checkBox->move(270, 10);
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
    connect(buttonEdit, &QPushButton::clicked, uiElementEventHandler, &UIElementEventHandler::on_buttonEdit_clicked);
}
QTimeEdit* UIElementFactory::CreateTimeEditor(QWidget *containerWidget, int coordinate_x, int coordinate_y, const QTime& time)
{
    QTimeEdit* TimeEdit = new QTimeEdit(containerWidget);
    TimeEdit->setFixedSize(70, 30);
    TimeEdit->move(coordinate_x, coordinate_y);

    // Встановлення часу
    TimeEdit->setTime(time);

    TimeEdit->show();
    return TimeEdit;
}



QLineEdit* UIElementFactory::CreateLineEdit(QWidget *containerWidget, const WidgetGeometry &geometry)
{
    QLineEdit* lineEdit = new QLineEdit(containerWidget);
    lineEdit->setFixedSize(geometry.width, geometry.height);
    lineEdit->move(geometry.xPos, geometry.yPos);
    lineEdit->show();
    return lineEdit;
}
void UIElementFactory::CreateButtonSetImage(QWidget *conteinerWidget, int itemId, const WidgetGeometry& geometry)
{
    QPushButton* ButtonSetImage = new QPushButton(conteinerWidget);
    ButtonSetImage->setObjectName("ButtonSetImage");  // Встановлення об'єктного імені
    ButtonSetImage->setFixedSize(geometry.width, geometry.height);
    ButtonSetImage->move(geometry.xPos, geometry.yPos);
    ButtonSetImage-> setIcon(QIcon(":/resource/Img_load_box_fill@3x.png"));
    ButtonSetImage->setIconSize(QSize(40, 40));
    ButtonSetImage->show();
    ButtonSetImage->setProperty("ItemId",itemId);
    connect(ButtonSetImage, &QPushButton::clicked, uiElementEventHandler, &UIElementEventHandler::on_ButtonSetImage_clicked);
}
void UIElementFactory::CreateButtonAddImage(QWidget *containerWidget, const WidgetGeometry &geometry)
{
    QPushButton* addButton = new QPushButton("Add Image", containerWidget);
    addButton->setFixedSize(geometry.width, geometry.height);
    addButton->move(geometry.xPos, geometry.yPos);
    addButton->show();
     connect(addButton, &QPushButton::clicked, uiElementEventHandler, &UIElementEventHandler::on_ButtonAddImage_clicked); // Connect to appropriate slot if needed
}

void UIElementFactory::CreateButtonBox(QWidget *containerWidget, int cordinate_x, int cordinate_y)
{

    QDialogButtonBox* buttonBox = new QDialogButtonBox(containerWidget);

      // Add Save and Cancel buttons
      buttonBox->addButton(tr("Save"), QDialogButtonBox::AcceptRole);
      buttonBox->addButton(tr("Cancel"), QDialogButtonBox::RejectRole);

      // Move the button box to the specified coordinates
      buttonBox->move(cordinate_x, cordinate_y);
    // Connect the accepted and rejected signals to the respective slots
    connect(buttonBox, &QDialogButtonBox::accepted, uiElementEventHandler, &UIElementEventHandler::onButtonBoxAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, uiElementEventHandler, &UIElementEventHandler::onButtonBoxRejected);
}


