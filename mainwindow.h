#pragma once

#include <QMainWindow>
#include "contactlistprovider.h"
#include <QMessageBox>
#include <QListWidget>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void on_ContactListWidgetModel_clicked(const QModelIndex &index);
    void cancelCall();
    void on_searchLine_textEdited(const QString &arg1);
    void on_changeView_clicked();
    void favorite_button_clicked();
    void on_showFavorite_clicked();
    
private:
    Ui::MainWindow *ui;
    QMessageBox *callScreen;
    ContactListProvider * contactListProvider;
    Database * favorite;
    void fillListWidgetView(const QVector<QPair<QString, QString>> &list);
    QIcon getItemIcon(const QString &path);
    QSize listItemSize;
    QSize gridItemZize;
    const int iconSize = 40;
    QSize itemButtonSizeListMode;
    QSize itemButtonSizeGridMode;
    void setItemSize(const QSize &size, const QSize &buttonSize);
    bool listView = true;
    bool onlyFavorite = true;
    void setListView();
    void setGridView();
};
