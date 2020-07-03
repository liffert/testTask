#pragma once
#include <QtCore>
#include <atomic>

class ContactListProvider {
private:
    QVector<QPair<QString, QString>> list;
    std::atomic<bool> callState;
public:
    QVector<QPair<QString, QString>> getActualContactList();
    ContactListProvider();
    void call(int id);
    void endCall();
};

