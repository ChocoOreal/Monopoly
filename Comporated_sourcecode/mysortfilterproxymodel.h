#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QObject>

class mySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    mySortFilterProxyModel(QObject* parent = 0);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // MYSORTFILTERPROXYMODEL_H
