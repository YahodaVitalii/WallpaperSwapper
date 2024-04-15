#ifndef WLAPPERIMAGE_H
#define WLAPPERIMAGE_H
#include <QString>

class WlapperImage
{
    QString name;
    QString url;
    int height;
    int width;
public:
    WlapperImage();

        QString getName() const;
        QString getUrl() const;
        int getHeight() const;
        int getWidth() const;

        void setName(const QString &newName);
        void setUrl(const QString &newUrl);
        void setHeight(int newHeight);
        void setWidth(int newWidth);
};

#endif // WLAPPERIMAGE_H
