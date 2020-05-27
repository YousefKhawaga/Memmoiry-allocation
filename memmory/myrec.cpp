#include "myrec.h"

Myrec::Myrec(int x, int y, int w, int h,int index)
{
    rec = QRectF(x,y,w,h);
    this->index = index;
}

void Myrec::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen;
    pen.setWidth(3);
    painter->setPen(pen);
    painter->fillRect(rec,brush);
    painter->drawRect(rec);
}

void Myrec::setBrush(QBrush brush)
{
    this->brush = brush;
}

QRectF Myrec::boundingRect() const
{
    return rec;
}

void Myrec::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit dellacotian(index);
}

void Myrec::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        emit table(index);
}
