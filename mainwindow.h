#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include "viewmodel.h"

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
    void Aplhabetical_buttonClicked();
    
    void on_ContactListView_clicked(const QModelIndex &index);
    void hideRow(const int row, const bool hide);
    
private:  
    Ui::MainWindow *ui;
    QMessageBox *callScreen;
    ViewModel *viewModel;
    void resizeEvent(QResizeEvent*);
    
    
    void fillListWidgetView(const QVector<Contact> &list);
    void setAlphabeticalJumbButtomBlock(const QVector<char> &letters);
    

    QSize listItemSize;
    QSize gridItemZize;
    QSize alphabeticalJumpButtonSize;
    QSize itemButtonSizeListMode;
    QSize itemButtonSizeGridMode;
    const int iconSize = 40;
    
    void setItemSize(const QSize &size, const QSize &buttonSize, Qt::Alignment alignment);
    bool listView = true;
    bool onlyFavorite = false;
    void setListView();
    void setGridView();
    void addItemButtons();
    void update();
};
