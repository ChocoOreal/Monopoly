#ifndef MYMODELVIEW_H
#define MYMODELVIEW_H

#include <QObject>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <vector>

using std::string; using std::vector;

class MainWindow;
class FilterSortProperty;

class myModelView
{
private:
    MainWindow *mainWindow;
    QStandardItemModel *cellData, *playerData, *cellDataSwap, *playerDataSwap;
    FilterSortProperty *propertyFilterSort;

public:
    myModelView();

    void attachViewWithModel(QAbstractItemView *view, int idModel);
    void setTypeFilterProperty(const string &type, const QString &player);

    vector<string> queryInforPlayer(int idPlayer);
    bool canBuy(int id);

    void updateCellData(int idCell, vector <string> info);
    void updatePlayerData(int idPlayer, vector <string> info);

    ~myModelView();
};

class FilterSortProperty : public QSortFilterProxyModel
{
    Q_OBJECT

private:
    string typeFilter;
    QString playerDoTask;

    bool canBuild(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const;
    bool canSell(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const;
    bool canMortgage(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const;
    bool canRedeem(QAbstractItemModel *&model, int source_row, const QModelIndex &source_parent) const;

public slots:
    void setTypeForFillter(const string &type, const QString &playerDoTask);

public:
    FilterSortProperty(QObject* parent = nullptr);
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // MYMODELVIEW_H
