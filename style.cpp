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


