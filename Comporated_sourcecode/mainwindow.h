#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainScene.h"
#include "cellitem.h"
#include "mysortfilterproxymodel.h"
#include <QDebug>
#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QStandardItemModel>

class CommandHandler;
class RunningGameMode;
class myModelView;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using std::string; using std::vector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void updatePlayer(int idPlayer, vector <string> info);
    void updateDiceData(int number, int idDice);

    void showCellInfo(int idCell);
    string showMessageBox(const string &text, const vector <string> &listQuery = {}, const bool waitResponde = false);

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CommandHandler *invoker = nullptr;
    MainScene *scene = nullptr;
    myModelView *gameModel = nullptr;

    int posPiece = 1;

public:
    friend RunningGameMode;

private slots:
    void on_buttonGo_clicked();
    void on_manageButton_clicked();
};
#endif // MAINWINDOW_H
