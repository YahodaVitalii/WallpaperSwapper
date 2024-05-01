#include "wlapperimage.h"

WlapperImage::WlapperImage()
{

}

int WlapperImage::getId() const
{
    return id;
}
QString WlapperImage::getName() const {
    return name;
}

QString WlapperImage::getUrl() const {
    return url;
}

int WlapperImage::getHeight() const {
    return height;
}

int WlapperImage::getWidth() const {
    return width;
}



void WlapperImage::setId(int newId)
{
    id = newId;
}

void WlapperImage::setName(const QString &newName) {
    name = newName;
}

void WlapperImage::setUrl(const QString &newUrl) {
    url = newUrl;
}

void WlapperImage::setHeight(int newHeight) {
    height = newHeight;
}

void WlapperImage::setWidth(int newWidth) {
    width = newWidth;
}
