#include "cellitem.h"
#include "mainwindow.h"

CellItem::CellItem()
{

}

CellItem::CellItem( QPointF leftTop, int width, int height, int idCell, MainWindow *mainWindow)
{
    CellItem::leftTop = leftTop;
    CellItem::width = width;
    CellItem::height = height;
    CellItem::idCell = idCell;
    CellItem::mainWindow = mainWindow;
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Ouh, " << this->idCell;
    mainWindow->showCellInfo(idCell);
    QGraphicsItem::mousePressEvent(event);
}
