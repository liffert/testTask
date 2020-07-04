#pragma once
#include <QtCore>
#include <atomic>
#include "contact.h"

class ContactListProvider {
private:
    QVector<Contact> list;
    std::atomic<bool> callState;
public:
    QVector<Contact> getActualContactList();
    ContactListProvider();
    void call(const int id);
    void endCall();
};

