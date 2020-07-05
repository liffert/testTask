#include "contactlistprovider.h"
#include <atomic>
#include <chrono>


QVector<Contact> ContactListProvider::getActualContactList(){
    list = {
        {"Sam Bradly", ":/icons/img/icon1", 1},
        {"Lucy Carter", ":/icons/img/icon2", 2},
        {"Natalia Govov", ":/icons/img/icon1", 3},
        {"Unknown person", ":/icons/img/icon3", 4},
        {"Breath Master", ":/icons/img/icon4", 5},
        {"Hello World", ":/icons/img/icon6", 6},
        {"Anne Hathaway", ":/icons/img/icon6", 7},
        {"Car seller", ":/icons/img/icon7", 8},
        {"Roby Roben", ":/icons/img/icon1", 9},
        {"Hellen Close", ":/icons/img/icon8", 10},
        {"Andy Sanders", ":/icons/img/icon9", 11},
        {"Cris Titus", ":/icons/img/icon1", 12},
        {"Sunken Ring", ":/icons/img/icon1", 13}
    };
    return list;
}

void ContactListProvider::call(const int id) {
    callState = true;
    qDebug() << "Calling to " << id << " " << std::find_if(list.begin(), list.end(), [id](Contact &obj){
        return obj.getId() == id;
    })->getName();
    auto startCall = std::chrono::system_clock::now();
    while(std::chrono::system_clock::now() - startCall < std::chrono::seconds(10) && callState){
        qApp->processEvents();   
    }
    qDebug() << "End call";
}

void ContactListProvider::endCall() {
    callState = false;
}
