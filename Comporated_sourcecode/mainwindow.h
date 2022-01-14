#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mainScene.h"
#include "cellitem.h"
#include "mysortfilterproxymodel.h"
#include <unordered_map>
#include <QDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QStandardItemModel>
#include <QTimer>

class CommandHandler;
class RunningGameMode;
class myModelView;
class LabelInformationPlayer;
class AnimateText;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using std::string; using std::vector; using std::unordered_map;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void updateTurnPlayer(int idPlayer);
    void updateInTaskPlayer();

public:
    static Qt::GlobalColor colorOfPlayer[4];

    MainWindow(int numPlayer, QWidget *parent = nullptr);
    void runWhenStart();

    void updateCell(int idCell, vector <string> info);
    void updatePlayer(int idPlayer, vector <string> info);
    void updateDiceData(int number, int idDice);
    void updateButtonOfPlayer(int idPlayer, QPushButton* button, bool show = false);
    void updateGameStatus(vector <string> listGameStatus);
    void updateInforBetweenWindow(int id); //Call this function to notify the id of elements have chosen between windows

    void showCellInfo(int idCell);
    string showMessageBox(const string &text, const vector <string> &listQuery = {}, const bool waitResponde = false);
    void showButtonOfPlayer(int idPlayer);

    vector<string> queryInfoPlayer(int idPlayer);

    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    CommandHandler *invoker = nullptr;
    MainScene *scene = nullptr;
    myModelView *gameModel = nullptr;
    LabelInformationPlayer *playerLabel;
    vector <int> idChose;
    vector <string> gameStatus;
    vector < unordered_map<QPushButton*, bool> > listButtonOfPlayer;
    AnimateText *animatorText = nullptr;

    int numberOfPlayer;
    int playerInTask = 0;

    int posPiece = 1;

public:
    friend RunningGameMode;

private slots:
    void on_buttonGo_clicked();
    void on_buttonBuy_clicked();
    void on_manageButton_clicked();
    void on_bankruptButton_clicked();
    void on_listPlayer_clicked(const QModelIndex &index);
    void on_homeButton_clicked();
    void on_toolButton_clicked();

signals:
    void showSetting();
};
#endif // MAINWINDOW_H
