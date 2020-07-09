#include "viewmodel.h"
#include <QListWidgetItem>

ViewModel::ViewModel(QColor background, QColor foreground, const int iconSize) : backgroundColor(background), foregroundColor(foreground), iconSize(iconSize) {
    contactListProvider = new ContactListProvider();
    alphabeticalJump = new AlphabeticalJump();
    model = new QStandardItemModel();
}

ViewModel::~ViewModel() {
    delete model;
    delete contactListProvider;
    delete alphabeticalJump;
}

void ViewModel::update() {
    setModel(contactListProvider->getActualContactList());
}

QVector<char> ViewModel::updateWithAlphabeticalJumpService() {
    auto contactList = contactListProvider->getActualContactList();
    auto letters = alphabeticalJump->getAvaliableLetters(contactList);
    setModel(contactList);
    return letters;
}

QStandardItemModel *ViewModel::getModel() const{
    return model;
}

const QModelIndex ViewModel::getItemIndex(const int row, const int column) {
    return model->index(row, column);
}

const QStandardItem *ViewModel::getItem(const QModelIndex &index) const {
    return model->itemFromIndex(index);
}

void ViewModel::search(const QString &arg1, bool onlyFavorite) {
    if(arg1 == ""){
        for(int i = 0; i < model->rowCount(); i++){
            int id = dynamic_cast<CustomItem *>(model->item(i))->getId();
            if(onlyFavorite){
                if(contactListProvider->contactInFavoritList(id)){
                    emit hideRow(i, false);
                }
            }
            else{
                emit hideRow(i, false);
            }
        }
    }
    for(int i = 0; i <  model->rowCount(); i++){
        if(model->item(i)->text().toUpper().toStdString().find(arg1.toUpper().toStdString()) == std::string::npos){
           emit hideRow(i, true);
        }
        else {
            if(onlyFavorite){
                int id = dynamic_cast<CustomItem *>(model->item(i))->getId();
                if(contactListProvider->contactInFavoritList(id)){
                    emit hideRow(i, false);
                }
            }
            else{
                emit hideRow(i, false);
            }
        }
    }
}

bool ViewModel::favoritePressed(const QModelIndex &index, bool onlyFavorite) {
    int id = dynamic_cast<CustomItem *>(model->itemFromIndex(index))->getId();
    bool state = contactListProvider->contactInFavoritList(id);
    contactListProvider->setContactFavoriteState(id, !state);
    if(state && onlyFavorite){
        emit hideRow(index.row(), true);
    }
    return !state;
}

void ViewModel::call(const QModelIndex &index) {
    contactListProvider->call(dynamic_cast<CustomItem *>(model->itemFromIndex(index))->getId());
}

void ViewModel::favoriteFilter(const bool onlyFavorite, const QString &searchLineText) {
    if(!onlyFavorite){
        search(searchLineText, onlyFavorite);
    }
    else{
        for(int i = 0; i < model->rowCount(); i++){
            int id = dynamic_cast<CustomItem *>(model->item(i))->getId();
            if(!contactListProvider->contactInFavoritList(id)) {
                emit hideRow(i, true);
            }
        }
    }
    
}

bool ViewModel::isFavoriteItem(const QModelIndex &index) {
    return contactListProvider->contactInFavoritList(dynamic_cast<CustomItem *>(model->itemFromIndex(index))->getId());
}

void ViewModel::endCall() {
    contactListProvider->endCall();
}

QModelIndex ViewModel::jumpTo(const char letter) {
    for(int i = 0; i < model->rowCount(); i++){
        if(model->item(i)->text().toUpper().front().unicode() == letter){
            return model->index(i, 0);
        }
    }
}

void ViewModel::setItemSize(const QSize &size, const int row, const int column) {
    model->item(row, column)->setSizeHint(size);
}

void ViewModel::setItemTextAlignment(const Qt::Alignment alignment, const int row, const int column) {
    model->item(row, column)->setTextAlignment(alignment);
}

int ViewModel::getCount() const {
    return model->rowCount();
}

void ViewModel::setModel(const QVector<Contact> &contactList){
    model->clear();
    for(const auto &iter : contactList){
        CustomItem *item = new CustomItem();
        item->setId(iter.getId());
        item->setIcon(getItemIcon(iter.getIconPath()));
        item->setText(iter.getName());
        item->setBackground(backgroundColor);
        item->setForeground(foregroundColor);
        model->appendRow(item);
    }
}

QIcon ViewModel::getItemIcon(const QString &path) {
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
