#include "wallpaperimage.h"

WallpaperImage::WallpaperImage()
{

}

int WallpaperImage::getId() const
{
    return id;
}
QString WallpaperImage::getName() const {
    return name;
}

QString WallpaperImage::getUrl() const {
    return url;
}

int WallpaperImage::getHeight() const {
    return height;
}

int WallpaperImage::getWidth() const {
    return width;
}



void WallpaperImage::setId(int newId)
{
    id = newId;
}

void WallpaperImage::setName(const QString &newName) {
    name = newName;
}

void WallpaperImage::setUrl(const QString &newUrl) {
    url = newUrl;
}

void WallpaperImage::setHeight(int newHeight) {
    height = newHeight;
}

void WallpaperImage::setWidth(int newWidth) {
    width = newWidth;
}
