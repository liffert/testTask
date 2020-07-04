#include "database.h"
#include <algorithm>

Database::Database(const QString &databaseName) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    if(db.open()){
       auto tables = db.tables();
       if(std::find(tables.begin(), tables.end(), "Favorite") == tables.end()){
           QSqlQuery query;
           if(!query.exec("CREATE TABLE Favorite (name varchar(100))")){
               qDebug() << query.lastError();
               qApp->exit(1);
           }
       }
    }
    else{
        qDebug() << db.lastError();
        qApp->exit(1);
    }
}

void Database::rebuildDatabase(const QStringList &actualContactList) {
    QSqlQuery query;
    if(!query.exec("SELECT * FROM Favorite")){
        qDebug() << query.lastError();
        qApp->exit(1);
    }
    while(query.next()){
        QString item = query.value(0).toString();
        if(std::find(actualContactList.begin(), actualContactList.end(), item) == actualContactList.end()){
            del(item);
        }
    }
}

bool Database::exist(const QString &item) {
    QSqlQuery query;
    query.prepare("SELECT * FROM Favorite WHERE name = :name");
    query.bindValue(":name", item);
    if(!query.exec()){
        qDebug() << query.lastError();
        qApp->exit(1);
    }
    return query.next();
}

void Database::insert(const QString &item) {
    QSqlQuery query;
    query.prepare("INSERT INTO Favorite values (?)");
    query.addBindValue(item);
    if(!query.exec()){
        qDebug() << query.lastError();
        qApp->exit(1);
    }
}

void Database::del(const QString &item) {
    QSqlQuery query;
    query.prepare("DELETE FROM Favorite WHERE name = ?");
    query.addBindValue(item);
    if(!query.exec()){
        qDebug() << query.lastError();
        qApp->exit(1);
    }
}
