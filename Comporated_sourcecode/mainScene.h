#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class CellItem;

class MainScene : public QGraphicsScene
{
private:
    CellItem *cellItem[41];
    QGraphicsPixmapItem *board;
    QGraphicsPixmapItem *diceImage[2];

public:
    QGraphicsPixmapItem *piece = nullptr; //CHANGE: this will be private

public:
    explicit MainScene(QObject *parent = nullptr);

    void setupMainScene();
    void setupCell();
    void setDiceImage(int number, int idDice);
    void setPiece(QGraphicsPixmapItem *&piece, int idCell);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    ~MainScene();
};

#endif // MAINSCENE_H
