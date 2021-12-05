#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class MainScene : public QGraphicsScene
{
public:
    explicit MainScene(QObject *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MAINSCENE_H
