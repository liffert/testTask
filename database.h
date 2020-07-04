#pragma once
#include <QtSql>

class Database {
private:
    QSqlDatabase db;
    
public:
    Database(const QString &databaseName);
    void rebuildDatabase(const QStringList &actualContactList);
    bool exist(const QString &item);
    void insert(const QString &item);
    void del(const QString &item);
};

