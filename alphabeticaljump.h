#pragma once
#include "contact.h"
#include <QVector>

class AlphabeticalJump {
public:
    QVector<char> getAvaliableLetters(QVector<Contact> &list) const;
};

