#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QImage>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    
    itemButtonSizeGridMode.setWidth(25);
    itemButtonSizeGridMode.setHeight(25);
    itemButtonSizeListMode.setWidth(50);
    itemButtonSizeListMode.setHeight(50);
    listItemSize.setWidth(50);
    listItemSize.setHeight(50);
    gridItemZize.setWidth(100);
    gridItemZize.setHeight(100);
    
    favorite = new Database("db.Favorite");
    
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
    QStringList actualContactList;
    for(const auto &iter : list){
        actualContactList.push_back(iter.first);
        QListWidgetItem *item = new QListWidgetItem();
        item->setIcon(getItemIcon(iter.second));
        item->setText(iter.first);
        item->setTextAlignment(Qt::AlignmentFlag::AlignCenter);
        item->setBackground(QColor(77, 77, 77));
        item->setForeground(Qt::GlobalColor::white);
        ui->ContactListWidgetModel->addItem(item);
        QPushButton *but = new QPushButton();
        if(favorite->exist(iter.first)){
            but->setText("F");
        }
        else{
            but->setText("NF");
        }
        connect(but, SIGNAL(clicked()), this, SLOT(favorite_button_clicked()));
        ui->ContactListWidgetModel->setItemWidget(item, but);
    }
    favorite->rebuildDatabase(actualContactList);
}

void MainWindow::setItemSize(const QSize &size, const QSize &buttonSize) {
    for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
        ui->ContactListWidgetModel->item(i)->setSizeHint(size);
        qobject_cast<QPushButton *>(ui->ContactListWidgetModel->itemWidget(ui->ContactListWidgetModel->item(i)))->setFixedSize(buttonSize);
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
        ui->changeView->setText("Change view(List)");
    }
    else{
        setListView();
        ui->changeView->setText("Change view(Grid)");
    }
    listView = !listView;
}

void MainWindow::favorite_button_clicked(){
    QPushButton *but = qobject_cast<QPushButton *>(sender());
    for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
        if(ui->ContactListWidgetModel->itemWidget(ui->ContactListWidgetModel->item(i)) == but){
            if(favorite->exist(ui->ContactListWidgetModel->item(i)->text())){
                but->setText("NF");
                favorite->del(ui->ContactListWidgetModel->item(i)->text());    
            }
            else{
                but->setText("F");
                favorite->insert(ui->ContactListWidgetModel->item(i)->text()); 
            }
            break;
        }
    }
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
    setItemSize(listItemSize, itemButtonSizeListMode);
}

void MainWindow::setGridView() {
    ui->ContactListWidgetModel->setViewMode(QListWidget::IconMode);
    ui->ContactListWidgetModel->setDragDropMode(QListWidget::NoDragDrop);
    ui->ContactListWidgetModel->setWordWrap(true);
    setItemSize(gridItemZize, itemButtonSizeGridMode);
}

void MainWindow::on_showFavorite_clicked() {
    if(!onlyFavorite){
        on_searchLine_textEdited(ui->searchLine->text());
    }
    else{
        for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
            if(!favorite->exist(ui->ContactListWidgetModel->item(i)->text())){
                ui->ContactListWidgetModel->item(i)->setHidden(true);
            }
        }
    }
    if(onlyFavorite){
        ui->showFavorite->setText("Show all");
    }
    else {
        ui->showFavorite->setText("Show favorite");
    }
    onlyFavorite = !onlyFavorite;
}
