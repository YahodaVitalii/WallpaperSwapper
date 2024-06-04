#ifndef WEEKIMAGELIST_H
#define WEEKIMAGELIST_H


#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

class WeekImageList {
private:
    int id;
    QString name;

public:
    QMap<QString, int> images;
    // Конструктори
    WeekImageList();
    WeekImageList(QString name, const QMap<QString, int>& images);

    QString getName() const;
    void setName(const QString& name);

    // Геттери та сеттери
    int getId() const;
    void setId(int newId);

    QMap<QString, int> getImages() const;
    void setImages(const QMap<QString, int>& newImages);

    // Методи серіалізації та десеріалізації у формат JSON
    QString toJsonString() const;
    void fromJsonString(const QString& jsonString);
};

#endif // WEEKIMAGELIST_H
