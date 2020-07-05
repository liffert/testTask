#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include "contactlistprovider.h"
#include "database.h"
#include "customitem.h"
#include "contact.h"
#include "alphabeticaljump.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
private slots:
    void cancelCall();
    void on_searchLine_textEdited(const QString &arg1);
    void on_changeView_clicked();
    void favorite_button_clicked();
    void on_showFavorite_clicked();
    void on_ContactListWidgetModel_itemClicked(QListWidgetItem *item);
    void Aplhabetical_buttonClicked();
    
private:  
    Ui::MainWindow *ui;
    QMessageBox *callScreen;
    ContactListProvider * contactListProvider;
    Database * favorite;
    AlphabeticalJump * alphabeticalJump;
    
    void fillListWidgetView(const QVector<Contact> &list);
    void setAlphabeticalJumbButtomBlock(const QVector<char> &letters);
    
    QIcon getItemIcon(const QString &path);
    QSize listItemSize;
    QSize gridItemZize;
    QSize alphabeticalJumpButtonSize;
    QSize itemButtonSizeListMode;
    QSize itemButtonSizeGridMode;
    const int iconSize = 40;
    
    void setItemSize(const QSize &size, const QSize &buttonSize, int alignment);
    bool listView = true;
    bool onlyFavorite = false;
    void setListView();
    void setGridView();
};
