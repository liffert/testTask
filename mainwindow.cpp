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
    
    
    callScreen = new QMessageBox(this);
    callScreen->setStandardButtons(QMessageBox::Cancel);
    
    viewModel = new ViewModel(QColor(77, 77, 77), Qt::GlobalColor::white, iconSize);
    ui->ContactListView->setSpacing(1);
    ui->ContactListView->setIconSize(QSize(iconSize, iconSize));
    ui->ContactListView->setModel(viewModel->getModel());
    createAlphabeticalJumbButtomBlock();
    update();
    setListView();
    connect(callScreen, SIGNAL(rejected()), this, SLOT(cancelCall()));
    connect(viewModel, SIGNAL(hideRow(const int, const bool)), this, SLOT(hideRow(const int, const bool)));
}

MainWindow::~MainWindow() {
    delete ui;
    delete callScreen;
    delete viewModel;
}

void MainWindow::setAlphabeticalJumbButtomBlock(const QVector<char> &letters) {
    QLayoutItem *child;
    while ((child = ui->alphabeticalJumpScrollAreaContents->layout()->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }
    for(const char &iter : letters){
        QPushButton *but = new QPushButton(QString(iter));
        but->setFixedSize(alphabeticalJumpButtonSize);
        connect(but, SIGNAL(clicked()), this, SLOT(Aplhabetical_buttonClicked()));
        ui->alphabeticalJumpScrollAreaContents->layout()->addWidget(but);
    }
}

void MainWindow::setItemSize(const QSize &size, const QSize &buttonSize, Qt::Alignment alignment) {
    for(int i = 0; i < viewModel->getCount(); i++){
        viewModel->setItemSize(size, i);
        viewModel->setItemTextAlignment(alignment, i);
        QPushButton *but = qobject_cast<QPushButton *>(ui->ContactListView->indexWidget(viewModel->getItemIndex(i)));
        if (but != nullptr){
            but->setFixedSize(buttonSize);
        }
    }
}

void MainWindow::createAlphabeticalJumbButtomBlock() {
    auto * alphabeticalJumpLayout = new QVBoxLayout(ui->alphabeticalJumpScrollAreaContents);
    ui->alphabeticalJumpScrollArea->setWidgetResizable(true);
    alphabeticalJumpLayout->setSpacing(1);
    alphabeticalJumpLayout->setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void MainWindow::cancelCall() {
    viewModel->endCall();
    callScreen->hide();
}

void MainWindow::on_searchLine_textEdited(const QString &arg1) {
    viewModel->search(arg1, onlyFavorite);
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
    for(int i = 0; i < viewModel->getCount(); i++){
        auto index = viewModel->getItemIndex(i, 0);
        if(ui->ContactListView->indexWidget(index) == but){
            if(viewModel->setFavoriteState(index, onlyFavorite)){
                dynamic_cast<QPushButton *>(ui->ContactListView->indexWidget(index))->setIcon(QIcon(":/favoriteIcons/appIcons/F"));
            }
            else{
                dynamic_cast<QPushButton *>(ui->ContactListView->indexWidget(index))->setIcon(QIcon(":/favoriteIcons/appIcons/NF"));
            }
            break;
        }
    }
    ui->ContactListView->clearSelection();
}

void MainWindow::setListView() {
    ui->ContactListView->setViewMode(QListView::ListMode);
    setItemSize(listItemSize, itemButtonSizeListMode, Qt::AlignmentFlag::AlignCenter);
}

void MainWindow::setGridView() {
    ui->ContactListView->setViewMode(QListView::IconMode);
    ui->ContactListView->setDragDropMode(QListView::NoDragDrop);
    setItemSize(gridItemZize, itemButtonSizeGridMode, Qt::AlignmentFlag::AlignHCenter | Qt::AlignmentFlag::AlignBottom);
}

void MainWindow::addItemButtons() {
    for(int i = 0; i < viewModel->getCount(); i++){
        QPushButton *but = new QPushButton();
        auto index = viewModel->getItemIndex(i, 0);
        if(viewModel->isFavoriteItem(index)) {
            but->setIcon(QIcon(":/favoriteIcons/appIcons/F"));
        }
        else{
            but->setIcon(QIcon(":/favoriteIcons/appIcons/NF"));
        }
        but->setStyleSheet("background-color: #4D4D4D;");
        connect(but, SIGNAL(clicked()), this, SLOT(favorite_button_clicked()));
        ui->ContactListView->setIndexWidget(index, but);
    }
}

void MainWindow::update() {
    auto letters = viewModel->updateWithAlphabeticalJumpService();
    setAlphabeticalJumbButtomBlock(letters);
    addItemButtons();
    if(listView){
        setListView();
    }
    else{
        setGridView();
    }
}

void MainWindow::on_showFavorite_clicked() {
    onlyFavorite = !onlyFavorite;
    viewModel->favoriteFilter(onlyFavorite, ui->searchLine->text());
    if(onlyFavorite){
        ui->showFavorite->setText("Show all");
    }
    else {
        ui->showFavorite->setText("Show favorite");
    }
}

void MainWindow::Aplhabetical_buttonClicked() {
    char letter = qobject_cast<QPushButton *>(sender())->text().front().unicode();
    ui->ContactListView->setCurrentIndex(viewModel->jumpTo(letter));
}

void MainWindow::on_ContactListView_clicked(const QModelIndex &index) {
    callScreen->setText("Calling to " + viewModel->getItem(index)->text());
    callScreen->show();
    viewModel->call(index);
    callScreen->hide();
    ui->ContactListView->clearSelection();
}

void MainWindow::hideRow(const int row, const bool hide) {
    ui->ContactListView->setRowHidden(row, hide);
}

void MainWindow::resizeEvent(QResizeEvent *) {
    ui->ContactListView->setSpacing(1);
}
