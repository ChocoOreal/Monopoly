#include "cellitem.h"

CellItem::CellItem()
{

}

CellItem::CellItem( QPointF leftTop, int width, int height )
{
    CellItem::leftTop = leftTop;
    CellItem::width = width;
    CellItem::height = height;
}
