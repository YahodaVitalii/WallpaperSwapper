#include "style.h"

QString Style::getMainWindowStyle()
{
    return "QMainWindow{"
           "background-color: rgb(83, 190, 120);"
           "font-family:'Inter';"
           "}";
}

QString Style::getMainMenuButtonsStyle(){
    return "QPushButton{"
           "color:#ffffff;"
           "background:none;"
           "background-color: rgb(83, 190, 120);"
           "border: 1px solid rgb(255, 255, 255);"
           "border-radius: 20px;"
           "font-size:16px;"
           "font-weight:800;"
           "}"
           "QPushButton::hover{"
           "background-color: #FFFFFF;"
           "color:rgb(83, 190, 120);"
           "}";
}

QString Style::getTabsStyle()
{
    return "QWidget{"
           "background-color: rgb(255, 255, 255);"
           "border-top-left-radius: 50px;"
           " border-bottom-left-radius: 50px;"
           "}";
}

QString Style::getStandartTabStyle()
{
    return "QWidget{"
           "background-color: rgb(232, 248, 238);"
           "border-radius: 20px;"
           "}"
           "QPushButton{"
           "background-color: rgb(83, 190, 120);"
           "border-radius: 15px;"
           "font-family:'Inter';"
           "font-size:16px;"
           "font-weight:800;"
           "color: rgb(255, 255, 255);"
           "}"
           "QPushButton::hover{"
           "background-color: rgba(83, 190, 120, 200)"
           "}"

           "QPushButton#StandartTabDeleteButton{"
           "background-color: rgb(226, 123, 141);"
           "}"
           "QPushButton#StandartTabDeleteButton::hover{"
           "background-color: rgba(226, 123, 141,200);"
           "}"

           "QPushButton#StandartTabChooseButton{"
           " background-color: rgb(249, 177, 105);"
           "}"
           "QPushButton#StandartTabChooseButton::hover{"
           " background-color: rgba(249, 177, 105,200);"
           "}"

           "QPushButton#StandartTabSetButton{"
           "background-color: rgb(123, 145, 223);"
           "}"
           "QPushButton#StandartTabSetButton::hover{"
           "background-color: rgba(123, 145, 223,200);"
           "}"
            ;
}

QString Style::getTimeTabStyle()
{
    return "QWidget{"
           "background-color: rgb(232, 248, 238);"
           "border-radius: 20px;"
           "}";

}

QString Style::getMenuBarStyle()
{
    return
            "QWidget{"
            "background-color: rgb(232, 248, 238);"
            "border-radius: 20px;"
            "}"
            "QPushButton{"
            "color: rgb(182, 184, 186);"
            "font-size: 14px;"
            "}"
            "QPushButton::hover{"
            "color: rgb(182, 184, 186);"
            "text-decoration: underline;"
            "}"
            "QPushButton#TimeTabMenuBarPlusButton, QPushButton#ListOfImageMenuBarPlusButton{"
            "background-color: rgb(226, 123, 141);"
            "color: rgb(255, 255, 255);"
            "font-size: 40px;"
            "padding-bottom: 10px;"
            "}"
            "QPushButton#TimeTabMenuBarPlusButton:hover, QPushButton#ListOfImageMenuBarPlusButton:hover{"
            "background-color: rgba(226, 123, 141, 200);"
            "}";
}

QString Style::getImageListStyle()
{
    return             "QWidget{"
                       "background-color: rgb(232, 248, 238);"
                       "border-radius: 10px;}"
                       "QPushButton::hover{"
                       "background-color: rgba(182, 184, 186,80);"
                       "border-radius:2px;"
                       "}"
                       "QPushButton#buttonImage{"
                       "background-color: rgba(182, 184, 186,0);"
                       "}"
                       "QPushButton#buttonImage::hover{"
                       "background-color: rgba(182, 184, 186,80);"
                       "}";
}

QString Style::getTabWidgetStyle()
{
    return "QTabWidget::pane{"
           "border-radius: 10px;"
           "}"
           "QTabBar::tab:last {"
           "border-radius: 10px;"
           "}"
           "QTabBar::tab:first {"
           "border-radius: 10px;"
           "}";
}

QString Style::getIterfaceAdditionStyle()
{
    return "QWidget {"
           "background-color: rgb(255, 255, 255);"
           "border: 2px solid rgba(83, 190, 120, 76);"
           "font-family: 'Inter';"
           "font-size: 14px;"
           "font-weight: 800;"
           "color: rgb(182, 184, 186);"
           "}"
           "QPushButton {"
           "background-color: rgba(0, 0, 0, 0);"
           "border: none;"
           "}"
           "QLabel {"
           "background-color: rgba(182, 184, 186, 80);"
           "border: none;"
           "}"
           "QPushButton::hover {"
           "background-color: rgb(182, 184, 186);"
           "}"
           "QCheckBox {"
           "    spacing: 0px;"
           "    padding: 0px;"
           "    margin: 0px;"
           "border:none;"

           "}"
           "QCheckBox::indicator {"
           "    width: 160px;"
           "    height: 60px;"

           "}"
           "QCheckBox::indicator:unchecked {"
           "    image: url(:/resource/off-button.png);"
           "}"
           "QCheckBox::indicator:checked {"
           "    image: url(:/resource/on-button.png);"
           "}";
}

QString Style::getCreateTabStyle()
{
    return "QWidget{"

           "font-family:'Inter';"
           "font-size:14px;"
           "font-weight:800;"
           "color:rgb(182, 184, 186);"
           "}"
           "QPushButton#ButtonAddNewItemOfRandomList{"
           "background-color: rgb(83, 190, 120);"
           "color:rgb(255, 255, 255);"
           "border-radius: 10px;"
           "}"
           "QPushButton{"
           "background-color: rgb(255, 255, 255);"
           "border:1px solid rgb(182, 184, 186);"
           "padding:5px;"
            // "margin-left:5px;"
            "min-width:60px;"
            "}"
            "QLineEdit,QTimeEdit{"
            "background-color: rgb(255, 255, 255);"
            "border:1px solid rgb(182, 184, 186);"
            "}";

}

QString Style::getPressedImageButtonStyle()
{
    return "QPushButton{"
        "background-color: rgb(182, 184, 186);"
        "}";

}

QString Style::getSliderStyle()
{
    return
            "QPushButton{"
            "background-color: rgba(225, 225, 225,0);"
            "}"
            "QPushButton::hover{"
            "background-color: rgba(225, 225, 225,80);"
            "}";
}





