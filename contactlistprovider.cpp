#include "contactlistprovider.h"

QStringList ContactListProvider::getActualContactList() {
    QStringList list;
    list << "Sam Bradly" << "Lucy Carter" << "Natalia Govov" << "Unknown person";
    return list;
}

ContactListProvider::ContactListProvider() {}
