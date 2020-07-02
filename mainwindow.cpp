#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    
    ui->setupUi(this);
    contactListProvider = new ContactListProvider();
    fillListWidgetView(contactListProvider->getActualContactList());
    //ui->ContactListWidgetModel->item(1)->setHidden(true);
    ui->ContactListWidgetModel->setSpacing(1);
}

MainWindow::~MainWindow() {
    delete ui;
    delete contactListProvider;
}

void MainWindow::fillListWidgetView(const QStringList &list) {
    for(const auto &iter : list){
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(iter);
        item->setSizeHint(QSize(itemSize, itemSize));
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        item->setBackground(QColor(77, 77, 77));
        item->setForeground(Qt::GlobalColor::white);
        ui->ContactListWidgetModel->addItem(item);
    }
}


void MainWindow::on_ContactListWidgetModel_clicked(const QModelIndex &index) {
    qDebug() << index;
    //std::this_thread::sleep_for(std::chrono::seconds(2));
    //ui->ContactListWidgetModel->item(index.row())->setSelected(false);
}
