#ifndef APPSTATE_H
#define APPSTATE_H
#include "../imageloader.h"
#include "../wallpapersetter.h"
#include "models/wallpaperimage.h"

class AppState
{
public:
    AppState();
    ~AppState();
    setWallpeper(const QString &imagePath);
protected:
    WallpaperSetter* wallpaperSetter;
};

#endif // APPSTATE_H
