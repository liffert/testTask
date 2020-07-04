#pragma once
#include <QString>

class Contact {
private:
    QString name;
    QString iconPath;
    int id;
public:
    Contact(QString name, QString iconPath, int id);
    QString getName() const;
    QString getIconPath() const;
    int getId() const;
};

