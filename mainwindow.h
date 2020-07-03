#pragma once

#include <QMainWindow>
#include "contactlistprovider.h"
#include <QMessageBox>

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

private:
    Ui::MainWindow *ui;
    QMessageBox *callScreen;
    ContactListProvider * contactListProvider;
    QStringListModel *model;
    void fillListWidgetView(const QVector<QPair<QString, QString>> &list);
    QIcon getItemIcon(const QString &path);
    const int listItemSize = 50;
    const int gridItemZize = 75;
    const int iconSize = 40;
    void setItemSize(const int size);
    bool listView = true;
    void setListView();
    void setGridView();
};
