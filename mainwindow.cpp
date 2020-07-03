#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QListWidget>
#include <QPainter>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    
    ui->setupUi(this);
    callScreen = new QMessageBox(this);
    callScreen->setStandardButtons(QMessageBox::Cancel);
    
    contactListProvider = new ContactListProvider();
    fillListWidgetView(contactListProvider->getActualContactList());
    ui->ContactListWidgetModel->setSpacing(1);
    ui->ContactListWidgetModel->setIconSize(QSize(iconSize, iconSize));
    setListView();
    
    connect(callScreen, SIGNAL(rejected()), this, SLOT(cancelCall()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete contactListProvider;
    delete callScreen;
}

void MainWindow::fillListWidgetView(const QVector<QPair<QString, QString>> &list) {
    for(const auto &iter : list){
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon(getItemIcon(iter.second));
        item->setText(iter.first);
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        item->setBackground(QColor(77, 77, 77));
        item->setForeground(Qt::GlobalColor::white);
        ui->ContactListWidgetModel->addItem(item);
    }
}

void MainWindow::setItemSize(const int size) {
    QSize qsize(size, size);
    for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
        ui->ContactListWidgetModel->item(i)->setSizeHint(qsize);
    }
}


void MainWindow::on_ContactListWidgetModel_clicked(const QModelIndex &index) {
    callScreen->setText("Calling to " + ui->ContactListWidgetModel->item(index.row())->text());
    callScreen->show();
    contactListProvider->call(index.row());
    callScreen->hide();
    
    ui->ContactListWidgetModel->item(index.row())->setSelected(false);
}

void MainWindow::cancelCall() {
    contactListProvider->endCall();
    callScreen->hide();
}

void MainWindow::on_searchLine_textEdited(const QString &arg1) {
    if(arg1 == ""){
        for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
            ui->ContactListWidgetModel->item(i)->setHidden(false);
        }
    }
    for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
        if(ui->ContactListWidgetModel->item(i)->text().toStdString().find(arg1.toStdString()) == std::string::npos){
            ui->ContactListWidgetModel->item(i)->setHidden(true);
        }
        else {
            ui->ContactListWidgetModel->item(i)->setHidden(false);
        }
    }
}

void MainWindow::on_changeView_clicked() {
    if(listView){
        setGridView();
    }
    else{
        setListView();   
    }
    listView = !listView;
}


QIcon MainWindow::getItemIcon(const QString &path) {
    QImage image(path);
    image = image.scaled(iconSize, iconSize, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QSize size = image.size();
    QPixmap map(size);
    map.fill(Qt::GlobalColor::transparent);
    QPainter painter(&map);
    painter.setBrush(image);
    painter.setPen(Qt::GlobalColor::white);
    painter.drawRoundedRect(0, 0, iconSize, iconSize, iconSize / 2, iconSize / 2);
    return QIcon(map);
}

void MainWindow::setListView() {
    ui->ContactListWidgetModel->setViewMode(QListWidget::ListMode);
    setItemSize(listItemSize);
}

void MainWindow::setGridView() {
    ui->ContactListWidgetModel->setViewMode(QListWidget::IconMode);
    ui->ContactListWidgetModel->setDragDropMode(QListWidget::NoDragDrop);
    setItemSize(gridItemZize);
}
