#include "baseimagelist.h"

BaseImageList::BaseImageList() : id(-1) {}

BaseImageList::BaseImageList(QString name) : id(-1), name(name) {}

// Геттери та сеттери
int BaseImageList::getId() const {
    return id;
}

void BaseImageList::setId(int newId) {
    id = newId;
}

QString BaseImageList::getName() const {
    return name;
}

void BaseImageList::setName(const QString& newName) {
    name = newName;
}
