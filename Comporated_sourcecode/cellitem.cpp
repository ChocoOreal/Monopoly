#include "cellitem.h"
#include "mainScene.h"
#include "mainwindow.h"

MainWindow* CellItem::mainWindow = nullptr;

CellItem::CellItem()
{

}

CellItem::CellItem(QPointF leftTop, int width, int height, int idCell, MainScene *mainScene)
{
    CellItem::leftTop = leftTop;
    CellItem::width = width;
    CellItem::height = height;
    CellItem::idCell = idCell;
    CellItem::mainScene = mainScene;
}

void CellItem::setMainWindow(MainWindow *mainWindow)
{
    CellItem::mainWindow = mainWindow;
}

void CellItem::setHouse(int numberOfHouse)
{
    if (numberOfHouse == listHouse.size()) return;

    {
        QImage imageHouse;
        if (numberOfHouse <= 4) imageHouse = QImage("Image/house.png");
        else
        {
            imageHouse = QImage("Image/hotel.png");
            numberOfHouse = 1;
        }

        for (int i = 0; i < listHouse.size(); i++) delete listHouse[i];
        listHouse.clear();
        for (int i = 1; i <= numberOfHouse; i++)
        {
            QGraphicsPixmapItem *test = new QGraphicsPixmapItem( QPixmap::fromImage(imageHouse) );
            listHouse.push_back(test);
            mainScene->addItem(listHouse[i-1]);
            listHouse[i-1]->setParentItem( this );
            listHouse[i-1]->setScale(0.04);
            listHouse[i-1]->setPos(0 + 20 * (i-1), 5);
        }
    }
}

void CellItem::setSelected(bool selected)
{
    CellItem::selected = selected;
    update();
}

void CellItem::setColorOwner(Qt::GlobalColor color)
{
    CellItem::colorOwner = color;
    update();
}

void CellItem::changeNumberPlayerIn(bool add)
{
    if (add) numPlayerIn++; else numPlayerIn--;
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CellItem::mainWindow->showCellInfo(idCell);
    setSelected(true);
    QGraphicsItem::mousePressEvent(event);
}
