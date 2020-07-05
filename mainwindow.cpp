#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QImage>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow) {
    
    ui->setupUi(this);
    itemButtonSizeGridMode.setWidth(70);
    itemButtonSizeGridMode.setHeight(40);
    itemButtonSizeListMode.setWidth(50);
    itemButtonSizeListMode.setHeight(50);
    alphabeticalJumpButtonSize.setWidth(45);
    alphabeticalJumpButtonSize.setHeight(45);
    
    listItemSize.setWidth(50);
    listItemSize.setHeight(50);
    gridItemZize.setWidth(300);
    gridItemZize.setHeight(100);
    
    favorite = new Database("db.Favorite");
    alphabeticalJump = new AlphabeticalJump();
    
    contactListProvider = new ContactListProvider();
    auto contactList = contactListProvider->getActualContactList();
    auto letters = alphabeticalJump->getAvaliableLetters(contactList);
    setAlphabeticalJumbButtomBlock(letters);
    
    callScreen = new QMessageBox(this);
    callScreen->setStandardButtons(QMessageBox::Cancel);
    
    ui->ContactListWidgetModel->setSpacing(1);
    ui->ContactListWidgetModel->setIconSize(QSize(iconSize, iconSize));
    fillListWidgetView(contactList);
    setListView();
    connect(callScreen, SIGNAL(rejected()), this, SLOT(cancelCall()));
}

MainWindow::~MainWindow() {
    delete ui;
    delete contactListProvider;
    delete callScreen;
    delete alphabeticalJump;
}

void MainWindow::fillListWidgetView(const QVector<Contact> &list) {
    QStringList actualContactList;
    for(const auto &iter : list){
        actualContactList.push_back(iter.getName());
        CustomItem *item = new CustomItem();
        item->setId(iter.getId());
        item->setIcon(getItemIcon(iter.getIconPath()));
        item->setText(iter.getName());
        item->setBackground(QColor(77, 77, 77));
        item->setForeground(Qt::GlobalColor::white);
        ui->ContactListWidgetModel->addItem(item);
        QPushButton *but = new QPushButton();
        but->setStyleSheet("background-color: #4D4D4D;");
        if(favorite->exist(iter.getName())){
            but->setIcon(QIcon(":/favoriteIcons/appIcons/F"));
        }
        else{
            but->setIcon(QIcon(":/favoriteIcons/appIcons/NF"));
        }
        connect(but, SIGNAL(clicked()), this, SLOT(favorite_button_clicked()));
        ui->ContactListWidgetModel->setItemWidget(item, but);
    }
    favorite->rebuildDatabase(actualContactList);
}

void MainWindow::setAlphabeticalJumbButtomBlock(const QVector<char> &letters) {
    auto * alphabeticalJumpLayout = new QVBoxLayout(ui->alphabeticalJumpScrollAreaContents);
    ui->alphabeticalJumpScrollArea->setWidgetResizable(true);
    alphabeticalJumpLayout->setSpacing(1);
    alphabeticalJumpLayout->setAlignment(Qt::AlignmentFlag::AlignCenter);
    for(const char &iter : letters){
        QPushButton *but = new QPushButton(QString(iter));
        but->setFixedSize(alphabeticalJumpButtonSize);
        connect(but, SIGNAL(clicked()), this, SLOT(Aplhabetical_buttonClicked()));
        alphabeticalJumpLayout->addWidget(but);
    }
}

void MainWindow::setItemSize(const QSize &size, const QSize &buttonSize, int alignment) {
    for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
        ui->ContactListWidgetModel->item(i)->setSizeHint(size);
        ui->ContactListWidgetModel->item(i)->setTextAlignment(alignment);
        qobject_cast<QPushButton *>(ui->ContactListWidgetModel->itemWidget(ui->ContactListWidgetModel->item(i)))->setFixedSize(buttonSize);
    }
}

void MainWindow::cancelCall() {
    contactListProvider->endCall();
    callScreen->hide();
}

void MainWindow::on_searchLine_textEdited(const QString &arg1) {
    if(arg1 == ""){
        for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
            if(onlyFavorite){
                if(favorite->exist(ui->ContactListWidgetModel->item(i)->text())){
                    ui->ContactListWidgetModel->item(i)->setHidden(false);
                }
            }
            else{
                ui->ContactListWidgetModel->item(i)->setHidden(false); 
            }
        }
    }
    for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
        if(ui->ContactListWidgetModel->item(i)->text().toUpper().toStdString().find(arg1.toUpper().toStdString()) == std::string::npos){
            ui->ContactListWidgetModel->item(i)->setHidden(true);
        }
        else {
            if(onlyFavorite){
                if(favorite->exist(ui->ContactListWidgetModel->item(i)->text())){
                    ui->ContactListWidgetModel->item(i)->setHidden(false);
                }
            }
            else{
                ui->ContactListWidgetModel->item(i)->setHidden(false);
            }
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
                but->setIcon(QIcon(":/favoriteIcons/appIcons/NF"));
                favorite->del(ui->ContactListWidgetModel->item(i)->text());
                if(onlyFavorite){
                    ui->ContactListWidgetModel->item(i)->setHidden(true);
                }
            }
            else{
                but->setIcon(QIcon(":/favoriteIcons/appIcons/F"));
                favorite->insert(ui->ContactListWidgetModel->item(i)->text()); 
            }
            ui->ContactListWidgetModel->item(i)->setSelected(false);
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
    setItemSize(listItemSize, itemButtonSizeListMode, Qt::AlignmentFlag::AlignCenter);
}

void MainWindow::setGridView() {
    ui->ContactListWidgetModel->setViewMode(QListWidget::IconMode);
    ui->ContactListWidgetModel->setDragDropMode(QListWidget::NoDragDrop);
    setItemSize(gridItemZize, itemButtonSizeGridMode, Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);
}

void MainWindow::on_showFavorite_clicked() {
    onlyFavorite = !onlyFavorite;
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
}

void MainWindow::on_ContactListWidgetModel_itemClicked(QListWidgetItem *item) {
    callScreen->setText("Calling to " + item->text());
    callScreen->show();
    contactListProvider->call(dynamic_cast<CustomItem *>(item)->getId());
    callScreen->hide();
    item->setSelected(false);
}

void MainWindow::Aplhabetical_buttonClicked() {
    char letter = qobject_cast<QPushButton *>(sender())->text().front().unicode();
    for(int i = 0; i < ui->ContactListWidgetModel->count(); i++){
        if(ui->ContactListWidgetModel->item(i)->text().toUpper().front().unicode() == letter){
            ui->ContactListWidgetModel->setCurrentRow(i);
            break;
        }
    }
}
