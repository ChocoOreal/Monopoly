#include "mysortfilterproxymodel.h"

mySortFilterProxyModel::mySortFilterProxyModel(QObject *parent) : QSortFilterProxyModel(parent)
{

}

bool mySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index_1 = sourceModel()->index(source_row, 0, source_parent);

    if (sourceModel()->data(index_1).toInt() <= 20) return true; else return false;
}
