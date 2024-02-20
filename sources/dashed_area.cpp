#include <drivers_loader/dashed_area.hpp>

drivers_loader::dashed_area::dashed_area(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{ }

void drivers_loader::dashed_area::paint(QPainter* painter)
{
    QPen pen(Qt::DashLine);
    pen.setWidth(4);

    painter->setPen(pen);
    painter->drawRect(0, 0, width(), height());
}