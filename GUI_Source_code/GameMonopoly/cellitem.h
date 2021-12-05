#ifndef CELLITEM_H
#define CELLITEM_H

#include <QGraphicsItem>
#include <QPainter>

class CellItem : public QGraphicsItem
{

private:
    QPointF leftTop;
    int height, width;

public:
    CellItem();
    CellItem( QPointF leftTop, int width, int height);

    QRectF boundingRect() const override
    {
        return QRectF(0, 0, width, height);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        QPen pen( Qt::red, 1);
        painter->setPen(pen);
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
};

#endif // CELLITEM_H
