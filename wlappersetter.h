#ifndef WLAPPERSETTER_H
#define WLAPPERSETTER_H
#include <QString>
#include <Windows.h>
#include "wsexeptions.h"
#include <QDebug>

class WlapperSetter
{
public:
    WlapperSetter();
    bool setWallpaper(const QString &imagePath);
};

#endif // WLAPPERSETTER_H
