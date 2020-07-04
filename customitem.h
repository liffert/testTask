#pragma once
#include <QListWidgetItem>

class CustomItem : public QListWidgetItem {
private:
    int id;
public:
    int getId();
    void setId(int id);
};  
