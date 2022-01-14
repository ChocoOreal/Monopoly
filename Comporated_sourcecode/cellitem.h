#ifndef CELLITEM_H
#define CELLITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <vector>

class MainWindow;
class MainScene;

using std::vector;

class CellItem : public QGraphicsItem
{

private:
    static MainWindow *mainWindow;

    MainScene *mainScene;
    QPointF leftTop;
    vector <QGraphicsPixmapItem*> listHouse;
    int height, width;
    int idCell;
    Qt::GlobalColor colorOwner;
    bool selected = false;
    int numPlayerIn = 0;

public:
    CellItem();
    CellItem(QPointF leftTop, int width, int height, int idCell, MainScene *mainScene);

    static void setMainWindow(MainWindow *mainWindow);

    QRectF boundingRect() const override
    {
        return QRectF(0, 0, width, height);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        QPen pen;
        if (selected) pen = QPen( Qt::red, 5); else pen = QPen( Qt::black, 0);
        painter->setPen(pen);

        QColor colorAlpha = colorOwner;
        if (colorAlpha != Qt::GlobalColor::transparent) colorAlpha.setAlphaF(0.2);
        painter->setBrush(colorAlpha);

        painter->drawRect( boundingRect() );
    }

    int getHeight()
    {
        return height;
    }

    int getWidth()
    {
        return width;
    }

    void setHouse(int numberOfHouse);
    void setSelected(bool selected = false);
    void setColorOwner(Qt::GlobalColor color);
    void changeNumberPlayerIn(bool add);

    int getNumberPlayerIn() { return numPlayerIn; }

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // CELLITEM_H
