#pragma once

#include <QMainWindow>
#include "contactlistprovider.h"

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
    
private:
    Ui::MainWindow *ui;
    ContactListProvider * contactListProvider;
    QStringListModel *model;
    void fillListWidgetView(const QStringList &list);
    const int itemSize = 50;
};
