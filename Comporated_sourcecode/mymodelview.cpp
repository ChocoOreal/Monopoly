#include "mymodelview.h"
#include "mysortfilterproxymodel.h"
#include "mainwindow.h"
#include <QWidget>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QAbstractItemView>

myModelView::myModelView()
{
    //WILL DELETING: check show cell info
    cellData = new QStandardItemModel(4, 4);
    cellDataSwap = new QStandardItemModel(4, 4);
    proxyModel = new mySortFilterProxyModel;
    proxyModel->setSourceModel(cellData);
    for (int i = 1; i <= 40; i++) this->updateCellData(i, vector<string>(10, std::to_string(i) ) );

    //Make label header for cell model
    QStringList headerList;
    headerList << "ID" << "Loại ô" << "Tên" << "Miêu tả" << "Giá mua" << "Giá thuê gốc" << "Hệ số thuê" << "Giá mua nhà"
               << "Giá cầm cố" << "Chủ sở hữu" << "Số lượng nhà hiện tại" << "Giá thuê hiện tại" << "Tình trạng cầm cố";
    cellData->setHorizontalHeaderLabels(headerList);
    cellDataSwap->setVerticalHeaderLabels(headerList);

    playerData = new QStandardItemModel();
    playerDataSwap = new QStandardItemModel();

    //Make label header for player model
    headerList.clear();
    headerList << "ID" << "Nickname" << "Vị trí" << "Tên ảnh token" << "Số tiền" << "Ở tù" << "Thẻ ra tù";
    playerData->setHorizontalHeaderLabels(headerList);
    playerData->setVerticalHeaderLabels(headerList);
}

void myModelView::attachViewWithModel(QAbstractItemView *view, int idModel)
{
    switch (idModel) {
    case 1:
        view->setModel(cellData);
        break;
     case 2:
        view->setModel(cellDataSwap);
        break;
     case 3:
        view->setModel(playerData);
        break;
     case 4:
        view->setModel(playerDataSwap);
        break;
    }
}

//Update cell model by info given by Update command class
void myModelView::updateCellData(int idCell, vector <string> info)
{
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

myModelView::~myModelView()
{
    delete playerData;
    delete playerDataSwap;
    delete cellData;
    delete cellDataSwap;
}
