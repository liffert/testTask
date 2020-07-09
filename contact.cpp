#include "contact.h"

Contact::Contact(const QString name, const QString iconPath, const int id, const bool favorite) 
    : name(name), iconPath(iconPath), id(id), favorite(favorite) {}

QString Contact::getName() const {
    return name;
}

QString Contact::getIconPath() const {
    return iconPath;
}

int Contact::getId() const {
    return id;
}

bool Contact::isFavorite() const {
    return favorite;
}

void Contact::setFavorite(const bool favorite) {
    this->favorite = favorite;
}
