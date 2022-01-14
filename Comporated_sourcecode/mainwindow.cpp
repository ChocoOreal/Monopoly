#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CommandHandler.h"
#include "mymodelview.h"
#include "labelinformationplayer.h"
#include "propertymanager.h"
#include "animatetext.h"
#include <QPropertyAnimation>
#include <QTimer>
#include <queue>

Qt::GlobalColor MainWindow::colorOfPlayer[4] = {Qt::darkGreen, Qt::red, Qt::blue, Qt::yellow};

MainWindow::MainWindow(int numPlayer, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MainWindow::numberOfPlayer = numPlayer;

    scene = new MainScene(this);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
    ui->graphicsView->setScene(scene);

    gameModel = new myModelView();

    gameModel->attachViewWithModel(ui->tableCellInfo, 2);
    gameModel->attachViewWithModel(ui->listPlayer, 3);
    ui->listPlayer->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listPlayer->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listPlayer->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->listPlayer->hideColumn(2); ui->listPlayer->hideColumn(3); ui->listPlayer->hideColumn(5);
    ui->tableCellInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    listButtonOfPlayer.resize(numPlayer);

    vector<QWidget *> listLablePlayer;
    for (int i = 0; i < numPlayer; i++)
        listLablePlayer.push_back( this->findChild<QWidget *>("widget" + QString::number(i + 1) ) );
    playerLabel = new LabelInformationPlayer(listLablePlayer, this);

    animatorText = new AnimateText(this);
}

void MainWindow::runWhenStart()
{
    scene->setupMainScene(numberOfPlayer);

    showCellInfo(1);
    gameStatus.resize(3);

    for (int i = 0; i < numberOfPlayer; i++)
    {
        updateButtonOfPlayer(i, ui->buttonGo);
        updateButtonOfPlayer(i, ui->buttonBuy);
    }
    updateButtonOfPlayer(0, ui->buttonGo, true);

    QObject::connect(scene, &QGraphicsScene::changed, ui->graphicsView, &QGraphicsView::updateScene);

    this->update();
}

//Update elemets related to cell data
void MainWindow::updateCell(int idCell, vector<string> info)
{
    gameModel->updateCellData(idCell, info);
    if ( info[10] != " ") scene->setHouse(idCell, std::stoi(info[10]) ); //Update house elements

    //Update background color of cell as its owner
    int idPlayerOwner = playerLabel->getIdOfPlayer( QString::fromStdString(info[9]) );
    if ( idPlayerOwner >= 0 && idPlayerOwner < numberOfPlayer ) scene->colorCellAsOwner(idCell, colorOfPlayer[ idPlayerOwner ]);
        else scene->colorCellAsOwner(idCell, Qt::GlobalColor::transparent);

    showCellInfo(idCell);
}

void MainWindow::updateDiceData(int number, int idDice)
{
    scene->setDiceImage(number, idDice);
}

//Update elements related to player data
void MainWindow::updatePlayer(int idPlayer, vector<string> info)
{
    gameModel->updatePlayerData(idPlayer, info);
    playerLabel->setNamePlayer(idPlayer, QString::fromStdString(info[1]) );
    playerLabel->setAvatarPlayer(idPlayer, QString::fromStdString(info[3]) );

    scene->setPiece(idPlayer, std::stoi(info[2]) );
    ui->listPlayer->setCurrentIndex( ui->listPlayer->model()->index( playerInTask, 0) );
    if ( gameModel->canBuy(std::stoi(info[2])) && idPlayer == std::stoi(gameStatus[0]) )
        updateButtonOfPlayer(idPlayer, ui->buttonBuy, true);
    if (info[5] == "true") playerLabel->setInCellPlayer(idPlayer, true); else playerLabel->setInCellPlayer(idPlayer, false);
}

void MainWindow::updateButtonOfPlayer(int idPlayer, QPushButton *button, bool show)
{
    listButtonOfPlayer[idPlayer][button] = show;
    showButtonOfPlayer( playerInTask );
}

void MainWindow::updateGameStatus(vector<string> listGameStatus)
{
    if ( std::stoi(listGameStatus[1]) == 0 ) ui->buttonGo->setText("Xong lượt");
    //Cap nhat trang thai chuyen luot cho nguoi choi ke tiep
    if ( gameStatus.empty() || std::stoi(listGameStatus[0]) != std::stoi(gameStatus[0]) ) updateTurnPlayer( std::stoi(listGameStatus[0]) );
    MainWindow::gameStatus = listGameStatus;
}

void MainWindow::updateInforBetweenWindow(int id)
{
    idChose[1] = id;
}

void MainWindow::updateTurnPlayer(int idPlayer)
{
    ui->buttonGo->setText("Đi");
    updateButtonOfPlayer( playerInTask, ui->buttonGo);
    updateButtonOfPlayer(playerInTask, ui->buttonBuy);
    playerLabel->setInTurnPlayer(playerInTask, false);

    playerInTask = idPlayer; updateInTaskPlayer();
    updateButtonOfPlayer( playerInTask, ui->buttonGo, true);
    QString name = QString::fromStdString( gameModel->queryInforPlayer(idPlayer)[1] );
    ui->turnPlayerLabel->setText("Người chơi trong lượt: " + name);
    playerLabel->setInTurnPlayer(idPlayer, true);
}

void MainWindow::updateInTaskPlayer()
{
    QString name = QString::fromStdString( gameModel->queryInforPlayer(playerInTask)[1] );
    ui->inTaskLabel->setText("Người chơi đang thao tác: " + name);
}

void MainWindow::showCellInfo(int idCell)
{
    for (int i = 0; i < 40; i++) ui->tableCellInfo->hideColumn(i);
    ui->tableCellInfo->showColumn(idCell - 1);
    ui->tableCellInfo->resizeRowsToContents();
    scene->chooseCell(idCell);
}

void MainWindow::showButtonOfPlayer(int idPlayer)
{
    for (auto i = listButtonOfPlayer[idPlayer].begin(); i != listButtonOfPlayer[idPlayer].end(); i++)
        (*i).first->setVisible( (*i).second );
}

vector<string> MainWindow::queryInfoPlayer(int idPlayer)
{
    return gameModel->queryInforPlayer(idPlayer);
}

//Resize mainScene automatically when Main Window show up
void MainWindow::showEvent(QShowEvent *event)
{
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

//Resize mainScene automatically when Main Window changes size
void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    ui->tableCellInfo->resizeRowsToContents();
}

string MainWindow::showMessageBox(const string &text, const vector<string> &listQuery, const bool waitResponde)
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromStdString(text));

    if (waitResponde)
    {
        int numQuery = listQuery.size();
        if (numQuery != 0)
        {
            vector <QPushButton *> listButton(numQuery);
            for (int i = 0; i < numQuery; i++) listButton[i] = msgBox.addButton( QString::fromStdString(listQuery[i]), QMessageBox::AcceptRole);
            msgBox.exec();
            for (int i = 0; i < numQuery; i++)
            {
                if (msgBox.clickedButton() == listButton[i]) return listQuery[i];
            }
        }
        msgBox.exec();
        return "";
    }

    QGraphicsTextItem *textItem;
    textItem = scene->addText( QString::fromStdString(text), QFont("Times New Roman", 40) );
    textItem->setDefaultTextColor( Qt::darkYellow);
    textItem->setTextWidth(1000);
    textItem->setPos( 640 - textItem->textWidth() / 2, 300);
    animatorText->addText( textItem );

    return "";
}

void MainWindow::on_buttonGo_clicked()
{
    if (ui->buttonGo->text() == "Đi") invoker->doCommand(0); else invoker->doCommand(1);
}

void MainWindow::on_buttonBuy_clicked()
{
    invoker->doCommand(2);
    updateButtonOfPlayer(playerInTask, ui->buttonBuy);
    showButtonOfPlayer(playerInTask);
}

void MainWindow::on_manageButton_clicked()
{
    QModelIndexList model = ui->listPlayer->selectionModel()->selectedRows(0);
    QModelIndex modelIndexSelected = model.back();
    int idPlayerSelect = modelIndexSelected.data().toInt();
    QString playerDoTask = ui->listPlayer->model()->index(idPlayerSelect, 1).data().toString();

    idChose.clear();
    idChose.push_back( idPlayerSelect );

    PropertyManager *propertyManager = new PropertyManager (this, invoker, scene, gameModel, playerDoTask);
    propertyManager->setWindowModality(Qt::ApplicationModal);
    propertyManager->setAttribute(Qt::WA_DeleteOnClose);
    propertyManager->show();
}

void MainWindow::on_bankruptButton_clicked()
{
    idChose.push_back(playerInTask);
    invoker->doCommand(9);
    idChose.clear();
}

void MainWindow::on_listPlayer_clicked(const QModelIndex &index)
{
    playerInTask = ui->listPlayer->selectionModel()->selectedRows().back().data().toInt();
    updateInTaskPlayer();
    showButtonOfPlayer(playerInTask);
}

void MainWindow::on_homeButton_clicked()
{
    string ans = showMessageBox("Bạn có chắc muốn thoát không? Ván chơi hiện tại sẽ không thể tiếp tục nếu bạn trờ về",
                                {"Tiếp tục chơi", "Thoát"}, true);
    if (ans == "Tiếp tục chơi") return; else invoker->doCommand(10);
}

void MainWindow::on_toolButton_clicked()
{
    emit showSetting();
}

MainWindow::~MainWindow()
{
    delete MainWindow::scene;
    delete ui;
}

