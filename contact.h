#pragma once
#include <QString>

class Contact {
private:
    QString name;
    QString iconPath;
    int id;
    bool favorite;
public:
    Contact(const QString name, const QString iconPath, const int id, const bool favorite);
    QString getName() const;
    QString getIconPath() const;
    int getId() const;
    bool isFavorite() const;
    void setFavorite(const bool favorite);
};

