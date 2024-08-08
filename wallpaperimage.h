#ifndef WALLPAPERIMAGE_H
#define WALLPAPERIMAGE_H
#include <QString>

class WallpaperImage
{
    int id;
    QString name;
    QString url;
    int height;
    int width;
public:
    WallpaperImage();

    int getId() const;
    QString getName() const;
    QString getUrl() const;
    int getHeight() const;
    int getWidth() const;

    void setId(int newId);
    void setName(const QString &newName);
    void setUrl(const QString &newUrl);
    void setHeight(int newHeight);
    void setWidth(int newWidth);
};

#endif // WALLPAPERIMAGE_H
