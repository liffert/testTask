#pragma once
#include <QString>

class Contact {
private:
    QString name;
    QString iconPath;
    int id;
public:
    Contact(const QString name, const QString iconPath, const int id);
    QString getName() const;
    QString getIconPath() const;
    int getId() const;
};

