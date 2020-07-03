#include "contactlistprovider.h"
#include <atomic>
#include <chrono>


QVector<QPair<QString, QString>> ContactListProvider::getActualContactList() {
    list = {
        {"Sam Bradly", ":/icons/img/icon1"},
        {"Lucy Carter", ":/icons/img/icon2"},
        {"Natalia Govov", ":/icons/img/icon1"},
        {"Unknown person", ":/icons/img/icon3"},
        {"Breath Master", ":/icons/img/icon4"},
        {"Hello World", ":/icons/img/icon6"},
        {"Anne Hathaway", ":/icons/img/icon6"},
        {"Car seller", ":/icons/img/icon7"},
        {"Roby Roben", ":/icons/img/icon1"},
        {"Hellen Close", ":/icons/img/icon8"},
        {"Andy Sanders", ":/icons/img/icon9"},
        {"Cris Titus", ":/icons/img/icon1"},
        {"Sunken Ring", ":/icons/img/icon1"}
    };
    return list;
}

ContactListProvider::ContactListProvider() {}

void ContactListProvider::call(int id) {
    callState = true;
    qDebug() << "Calling to " << id << " " << list.at(id).first;
    auto startCall = std::chrono::system_clock::now();
    while(std::chrono::system_clock::now() - startCall < std::chrono::seconds(10) && callState){
        qApp->processEvents();   
    }
    qDebug() << "End call";
}

void ContactListProvider::endCall() {
    callState = false;
}
