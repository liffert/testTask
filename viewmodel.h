#pragma once
#include <QStandardItemModel>
#include <QObject>
#include <QPainter>
#include "contactlistprovider.h"
#include "customitem.h"
#include "contact.h"
#include "alphabeticaljump.h"


class ViewModel : public QObject {
    Q_OBJECT
private:
    QStandardItemModel *model;
    void setModel(const QVector<Contact> &contactList);
    ContactListProvider * contactListProvider;
    AlphabeticalJump * alphabeticalJump;
    QIcon getItemIcon(const QString &path);
    QColor backgroundColor;
    QColor foregroundColor;
    int iconSize;
public:
    ViewModel(QColor background, QColor foreground, const int iconSize);
    ~ViewModel();
    QVector<char> updateWithAlphabeticalJumpService();
    QStandardItemModel *getModel() const;
    const QModelIndex getItemIndex(const int row, const int column = 0) const;
    const QStandardItem *getItem(const QModelIndex &index) const;
    void search(const QString &arg1, bool onlyFavorite);
    bool setFavoriteState(const QModelIndex &index, bool onlyFavorite);
    void call(const QModelIndex &index) const;
    void favoriteFilter(const bool onlyFavorite, const QString &searchLineText);
    bool isFavoriteItem(const QModelIndex &index) const;
    QModelIndex jumpTo(const char letter) const;
    void setItemSize(const QSize &size, const int row, const int column = 0);
    void setItemTextAlignment(const Qt::Alignment alignment, const int row, const int column = 0);
    int getCount() const;
    void endCall();
    void update();
signals:
    void hideRow(const int row, const bool hide);
};

