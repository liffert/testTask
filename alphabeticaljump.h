#pragma once
#include <contact.h>
#include <QVector>

class AlphabeticalJump {
public:
    AlphabeticalJump();
    QVector<char> getAvaliableLetters(QVector<Contact> &list);
};

