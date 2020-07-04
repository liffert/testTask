#include "alphabeticaljump.h"
#include <algorithm>

AlphabeticalJump::AlphabeticalJump() {}

QVector<char> AlphabeticalJump::getAvaliableLetters(QVector<Contact> &list) {
    QVector<char> letters;
    std::sort(list.begin(), list.end(), [](Contact &first, Contact &second){
       return first.getName().toUpper() < second.getName().toUpper(); 
    });
    for(const auto & iter: list){
        char letter = iter.getName().toUpper().front().unicode();
        if(!letters.empty()){
            if(letters.back() != letter){
                letters.push_back(letter);
            }
        }
        else{
            letters.push_back(letter);
        }
    }
    return letters;
}
