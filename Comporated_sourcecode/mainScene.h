#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class CellItem;
class MainWindow;

class MainScene : public QGraphicsScene
{
    Q_OBJECT

private:
    MainWindow* mainWindow;
    CellItem *cellItem[41];
    QGraphicsPixmapItem *board;
    QGraphicsPixmapItem *diceImage[2];
    QGraphicsRectItem* locate[4];

public:
    QGraphicsPixmapItem *piece[4] = {nullptr};

public:
    explicit MainScene(QObject *parent = nullptr);

    void setupMainScene(int numPlayer);
    void setupCell();
    void setDiceImage(int number, int idDice);
    void setPiece(int idPlayer, int idCell);
    void setHouse(int idCell, int numberOfHouse);
    void chooseCell(int idCell);
    void colorCellAsOwner(int idCell, Qt::GlobalColor color);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    ~MainScene();
};

#endif // MAINSCENE_H
