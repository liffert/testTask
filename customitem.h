#pragma once
#include <QListWidgetItem>

class CustomItem : public QListWidgetItem {
private:
    int id;
public:
    int getId() const;
    void setId(const int id);
};  
