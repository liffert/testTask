#pragma once
#include <QStandardItem>

class CustomItem : public QStandardItem {
private:
    int id;
public:
    int getId() const;
    void setId(const int id);
};  
