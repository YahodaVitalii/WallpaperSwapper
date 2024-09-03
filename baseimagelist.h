#ifndef BASEIMAGELIST_H
#define BASEIMAGELIST_H


#include <QString>
#include <QJsonObject>
#include <QJsonDocument>

class BaseImageList {
protected:
    int id;
    QString name;

public:
    // Конструктор
    BaseImageList();
    BaseImageList(QString name);

    // Геттери та сеттери
    int getId() const;
    void setId(int newId);

    QString getName() const;
    void setName(const QString& newName);
};

#endif // BASEIMAGELIST_H
