#include "mainScene.h"

MainScene::MainScene(QObject *parent) : QGraphicsScene(parent)
{

}

void MainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF point = event->scenePos();
    qDebug() << point.x() << ' ' << point.y() << '\n';
}
