#include "contact.h"

Contact::Contact(QString name, QString iconPath, int id) : name(name), iconPath(iconPath), id(id) {}

QString Contact::getName() const {
    return name;
}

QString Contact::getIconPath() const {
    return iconPath;
}

int Contact::getId() const {
    return id;
}
