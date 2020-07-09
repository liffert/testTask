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
    void call(const int id);
    void endCall();
    bool contactInFavoritList(const int id);
    void setContactFavoriteState(const int id, const bool favorite);
};

