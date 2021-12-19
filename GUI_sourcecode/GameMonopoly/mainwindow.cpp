#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupMainScene();

    //WILL DELETING: check show cell info
    cellData = new QStandardItemModel(4, 4, this);
    cellDataSwap = new QStandardItemModel(4, 4, this);
    ui->tableCellInfo->setModel(cellDataSwap);
    for (int i = 1; i <= 40; i++) this->updateCellData(i, vector<string>(10, std::to_string(i) ) );
}

void MainWindow::setupMainScene()
{
    scene = new MainScene(this);

    ui->graphicsView->setScene(scene);

    //Load Board image. Stick it to mainScene
    QImage imageBoard("Image/Board.jpg");
    if (imageBoard.isNull()) qDebug() << "Error: Not found Board image!\n";
    board = scene->addPixmap( QPixmap::fromImage(imageBoard) );

    //Load Dice image and change position/size. Stick it to mainScene
    setDiceImage(dice1, 6, 1);
    setDiceImage(dice2 , 4, 2);

    //Load Cell area control
    setupCell();

    //Test set piece
    QImage imagePiece("Image/car.png");
    piece = scene->addPixmap( QPixmap::fromImage(imagePiece) );
    piece->setScale(0.05);

    setPiece(piece, posPiece);
}

void MainWindow::setupCell()
{
    int tmp = 134;

    //Cells at bottom
    for (int i = 10; i >= 2; i--)
    {
        cellItem[i] = new CellItem( QPointF(tmp,890), 84, 133, i, this);
        scene->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(tmp, 890) );
        tmp += 84;
    }

    //Cells at top
    tmp = 134;
    for (int i = 22; i <= 30; i++)
    {
        cellItem[i] = new CellItem( QPointF(tmp, 0), 84, 133, i, this);
        scene->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(tmp, 0) );
        tmp += 84;
    }

    //Cells on left
    tmp = 134;
    for (int i = 20; i >= 12; i--)
    {
        cellItem[i] = new CellItem( QPointF(0, tmp), 133, 84, i, this);
        scene->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(0, tmp) );
        tmp += 84;
    }

    //Cells on right
    tmp = 134;
    for (int i = 32; i <= 40; i++)
    {
        cellItem[i] = new CellItem( QPointF(890, tmp), 133, 84, i, this);
        scene->addItem( cellItem[i] );
        cellItem[i]->setPos( QPointF(890, tmp) );
        tmp += 84;
    }

    cellItem[1] = new CellItem( QPointF(890, 890), 134, 134, 1, this);
    scene->addItem( cellItem[1] );
    cellItem[1]->setPos( QPointF(890, 890) );

    cellItem[11] = new CellItem( QPointF(0, 890), 134, 134, 11, this);
    scene->addItem( cellItem[11] );
    cellItem[11]->setPos( QPointF(0, 890) );

    cellItem[21] = new CellItem( QPointF(0, 0), 134, 134, 21, this);
    scene->addItem( cellItem[21] );
    cellItem[21]->setPos( QPointF(0, 0) );

    cellItem[31] = new CellItem( QPointF(890, 0), 134, 134, 31, this);
    scene->addItem( cellItem[31] );
    cellItem[31]->setPos( QPointF(890, 0) );

    //Due to modulo property, numId 40 will become 0 after modulo with 40
    cellItem[0] = cellItem[40];
}

//Load image of dice to the mainScene
//+ number: number of dice need loading
//+ idDice: first or second dice, used for positioning image of dice
void MainWindow::setDiceImage(QGraphicsPixmapItem *&dice, int number, int idDice)
{
    if (dice != nullptr) scene->removeItem(dice);
    delete dice;

    //Name of dice has format: "dice" + number of dice
    QString imageName = "Image/dice";
    imageName = imageName + QString::number(number) + ".png";

    QImage imageDice(imageName);
    if (imageDice.isNull()) qDebug() << "Error: Not found Dice image!\n";
    dice = scene->addPixmap( QPixmap::fromImage(imageDice) );
    dice->setScale(0.2);
    //Put the first dice above the second dice
    if (idDice == 1) dice->setPos(1030, 0); else dice->setPos(1030, 70);
}

//Load image of piece to the right cell
void MainWindow::setPiece(QGraphicsPixmapItem *&piece, int idCell)
{
    piece->setParentItem( cellItem[idCell] );
    piece->setPos( cellItem[idCell]->getWidth() / 4,  cellItem[idCell]->getHeight() / 4 );
}

void MainWindow::showCellInfo(int idCell)
{
    for (int i = 0; i < 40; i++) ui->tableCellInfo->hideColumn(i);
    ui->tableCellInfo->showColumn(idCell - 1);
}

//Update cell model by info given by class Cell
void MainWindow::updateCellData(int idCell, vector <string> info)
{
    for (size_t i = 0; i < info.size(); i++)
    {
        QStandardItem* item = new QStandardItem( QString::fromStdString(info[i]) );
        cellData->setItem(idCell - 1, i, item);
        cellDataSwap->setItem(i, idCell-1, item->clone());
    }
}

//Resize mainScene automatically when Main Window show up
void MainWindow::showEvent(QShowEvent *event)
{
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    //qDebug() << scene->sceneRect().width() << " " << scene->sceneRect().height() << scene->sceneRect().x() << scene->sceneRect().y();
}

//Resize mainScene automatically when Main Window changes size
void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    //qDebug() << "Resize: " << scene->sceneRect().width() << " " << scene->sceneRect().height() << scene->sceneRect().x() << scene->sceneRect().y();
}

void MainWindow::on_buttonGo_clicked()
{
    qint32 resultDice = QRandomGenerator::global()->bounded(6) + 1;
    setDiceImage(dice1, resultDice, 1);
    posPiece += resultDice;
    resultDice = QRandomGenerator::global()->bounded(6) + 1;
    setDiceImage(dice2, resultDice, 2);
    posPiece += resultDice;

    setPiece(piece, posPiece % 40);
}

MainWindow::~MainWindow()
{
    delete MainWindow::scene;
    delete MainWindow::board;
    delete MainWindow::dice1;
    delete MainWindow::dice2;
    for (int i = 1; i <= 40; i++) delete cellItem[i];
    delete ui;
}

