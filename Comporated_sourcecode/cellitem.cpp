#include "cellitem.h"
#include "mainScene.h"

CellItem::CellItem()
{

}

CellItem::CellItem( QPointF leftTop, int width, int height, int idCell, MainScene *mainScene)
{
    CellItem::leftTop = leftTop;
    CellItem::width = width;
    CellItem::height = height;
    CellItem::idCell = idCell;
    CellItem::mainScene = mainScene;
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Ouh, " << this->idCell;
    //mainScene->showCellInfo(idCell);
    QGraphicsItem::mousePressEvent(event);
}
