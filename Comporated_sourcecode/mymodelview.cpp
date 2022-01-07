#include "mymodelview.h"
#include "mysortfilterproxymodel.h"
#include "mainwindow.h"
#include <QObject>
#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <Player.h>

myModelView::myModelView()
{
    //WILL DELETING: check show cell info
    cellData = new QStandardItemModel(4, 4);
    cellDataSwap = new QStandardItemModel(4, 4);
    for (int i = 1; i <= 40; i++) this->updateCellData(i, vector<string>(10, std::to_string(i) ) );


    //Make label header for cell model
    QStringList headerList;
    headerList << "ID" << "Loại ô" << "Tên" << "Miêu tả" << "Giá mua" << "Giá thuê gốc" << "Hệ số thuê" << "Giá mua nhà"
               << "Giá cầm cố" << "Chủ sở hữu" << "Số lượng nhà hiện tại" << "Giá thuê hiện tại" << "Tình trạng cầm cố";
    cellData->setHorizontalHeaderLabels(headerList);
    cellDataSwap->setVerticalHeaderLabels(headerList);

    playerData = new QStandardItemModel;
    playerDataSwap = new QStandardItemModel;

    //Make label header for player model
    headerList.clear();
    headerList << "ID" << "Nickname" << "Vị trí" << "Tên ảnh token" << "Số tiền" << "Ở tù";
    playerData->setHorizontalHeaderLabels(headerList);
    playerDataSwap->setVerticalHeaderLabels(headerList);

    propertyFilterSort = new FilterSortProperty;
    propertyFilterSort->setSourceModel(cellData);
}

void myModelView::attachViewWithModel(QAbstractItemView *view, int idModel)
{
    switch (idModel) {
     case 1:
        view->setModel(cellData); break;
     case 2:
        view->setModel(cellDataSwap); break;
     case 3:
        view->setModel(playerData); break;
     case 4:
        view->setModel(playerDataSwap); break;
     case 5:
        view->setModel(propertyFilterSort); break;
    }
}

void myModelView::setTypeFilterProperty(const string &type, const QString &player)
{
    propertyFilterSort->setTypeForFillter(type, player);
}

//Update cell model by info given by Update command class
void myModelView::updateCellData(int idCell, vector <string> info)
{
    info[9] = getNameOfIdPlayer( std::stoi(info[9]) ).toStdString();

    for (size_t i = 0; i < info.size(); i++)
    {
        QStandardItem* item = new QStandardItem( QString::fromStdString(info[i]) );
        cellData->setItem(idCell - 1, i, item);
        cellDataSwap->setItem(i, idCell-1, item->clone());
    }
}

//Update player model by info given Update command class
void myModelView::updatePlayerData(int idPlayer, vector<string> info)
{
    for (size_t i = 0; i < info.size(); i++)
    {
        QStandardItem* item = new QStandardItem( QString::fromStdString(info[i]) );
        playerData->setItem(idPlayer - 1, i, item);
        playerDataSwap->setItem(i, idPlayer-1, item->clone());
    }
}

QString myModelView::getNameOfIdPlayer(int idPlayer)
{
    return ( (idPlayer >= 0 && idPlayer < Player::InstanceCount) ? playerData->index(idPlayer - 1, 1).data().toString() : "");
}

myModelView::~myModelView()
{
    delete playerData;
    delete playerDataSwap;
    delete cellData;
    delete cellDataSwap;
    delete propertyFilterSort;
}

bool FilterSortProperty::canBuild(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const
{
    QModelIndex indexType = model->index(source_row, 1, source_parent);
    QModelIndex indexOwner = model->index(source_row, 9, source_parent);
    QModelIndex indexNumHouse = model->index(source_row, 10, source_parent);
    QString type = model->data(indexType).toString();
    QString owner = model->data(indexOwner).toString();
    int numHouse = model->data(indexNumHouse).toInt();

    if ( (type == "normalland") && (owner == playerDoTask) && (numHouse < 5)) return true; else return false;
}

bool FilterSortProperty::canSell(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const
{
    QModelIndex indexOwner = model->index(source_row, 9, source_parent);
    QModelIndex indexNumHouse = model->index(source_row, 10, source_parent);
    QString owner = model->data(indexOwner).toString();
    int numHouse = model->data(indexNumHouse).toInt();

    if ( (owner == playerDoTask) && (numHouse > 0) ) return true; else return false;
}

bool FilterSortProperty::canMortgage(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const
{
    QModelIndex indexType = model->index(source_row, 1, source_parent);
    QModelIndex indexOwner = model->index(source_row, 9, source_parent);
    QModelIndex indexNumHouse = model->index(source_row, 10, source_parent);
    QModelIndex indexMortgageStatus = model->index(source_row, 12, source_parent);
    QString type = model->data(indexType).toString();
    QString owner = model->data(indexOwner).toString();
    int numHouse = model->data(indexNumHouse).toInt();
    QString mortgageStatus = model->data(indexMortgageStatus).toString();

    if ( (type == "normalland" || type == "factory" || type == "railroad") && (owner == playerDoTask) && (numHouse == 0)
         && (mortgageStatus == "false") ) return true; else return false;
}

bool FilterSortProperty::canRedeem(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const
{
    QModelIndex indexOwner = model->index(source_row, 9, source_parent);
    QModelIndex indexMortgageStatus = model->index(source_row, 12, source_parent);
    QString owner = model->data(indexOwner).toString();
    QString mortgageStatus = model->data(indexMortgageStatus).toString();

    if ( (owner == playerDoTask) && (mortgageStatus == "true") ) return true; else return false;
}

FilterSortProperty::FilterSortProperty(QObject *parent) : QSortFilterProxyModel(parent)
{
    typeFilter = "";
    playerDoTask = "";
}

void FilterSortProperty::setTypeForFillter(const string &type, const QString &player)
{
    typeFilter = type;
    playerDoTask = player;
    invalidateFilter();
}

bool FilterSortProperty::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QAbstractItemModel *model = sourceModel();

    if (typeFilter == "build") return canBuild(model, source_row, source_parent);
    if (typeFilter == "sell") return canSell(model, source_row, source_parent);
    if (typeFilter == "mortgage") return canMortgage(model, source_row, source_parent);
    if (typeFilter == "redeem") return canRedeem(model, source_row, source_parent);
    return true;
}
