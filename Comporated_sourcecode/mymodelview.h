#ifndef MYMODELVIEW_H
#define MYMODELVIEW_H

#include <QObject>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <string>
#include <vector>

using std::string; using std::vector;

class QStandardItemModel;
class mySortFilterProxyModel;
class MainWindow;
class QAbstractItemView;

class myModelView
{
private:
    MainWindow *mainWindow;
    QStandardItemModel *cellData, *playerData, *cellDataSwap, *playerDataSwap;
    mySortFilterProxyModel *proxyModel;

public:
    myModelView();

    void attachViewWithModel(QAbstractItemView *view, int idModel);

    void updateCellData(int idCell, vector <string> info);
    void updatePlayerData(int idPlayer, vector <string> info);

    ~myModelView();
};

#endif // MYMODELVIEW_H
