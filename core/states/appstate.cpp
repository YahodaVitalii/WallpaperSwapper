#include "appstate.h"

AppState::AppState()
{
    wallpaperSetter = new WallpaperSetter();
}

AppState::~AppState()
{
    delete wallpaperSetter;
}

AppState::setWallpeper(const QString &imagePath)
{
    wallpaperSetter->setWallpaper(imagePath);
}
