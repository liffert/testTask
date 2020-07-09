#include "contactlistprovider.h"
#include <atomic>
#include <chrono>


QVector<Contact> ContactListProvider::getActualContactList(){
    list = {
        {"Sam Bradly", ":/icons/img/icon1", 1, false},
        {"Lucy Carter", ":/icons/img/icon2", 2, true},
        {"Natalia Govov", ":/icons/img/icon1", 3, false},
        {"Unknown person", ":/icons/img/icon3", 4, false},
        {"Breath Master", ":/icons/img/icon4", 5, false},
        {"Hello World", ":/icons/img/icon6", 6, false},
        {"Anne Hathaway", ":/icons/img/icon6", 7, true},
        {"Car seller", ":/icons/img/icon7", 8, false},
        {"Roby Roben", ":/icons/img/icon1", 9, false},
        {"Hellen Close", ":/icons/img/icon8", 10, false},
        {"Andy Sanders", ":/icons/img/icon9", 11, false},
        {"Cris Titus", ":/icons/img/icon1", 12, false},
        {"Sunken Ring", ":/icons/img/icon1", 13, false}
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

bool ContactListProvider::contactInFavoritList(const int id) {
    return std::find_if(list.begin(), list.end(), [id](Contact &obj){
        return obj.getId() == id;
    })->isFavorite();
}

void ContactListProvider::setContactFavoriteState(const int id, const bool favorite) {
    std::find_if(list.begin(), list.end(), [id](Contact &obj){
        return obj.getId() == id;
    })->setFavorite(favorite);
}
