#ifndef BASEIMAGELIST_H
#define BASEIMAGELIST_H

#include <QString>

class BaseImageList {
protected:
    int id;
    QString name;

public:
    BaseImageList();
    BaseImageList(QString name);

    int getId() const;
    void setId(int newId);

    QString getName() const;
    void setName(const QString& newName);
};

#endif // BASEIMAGELIST_H
