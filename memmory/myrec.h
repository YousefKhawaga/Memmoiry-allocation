#ifndef MYREC_H
#define MYREC_H
#include <QGraphicsObject>
#include <QPainter>



class Myrec :public QGraphicsObject
{
    Q_OBJECT
public:
    Myrec(int x,int y,int w,int h,int index);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void setBrush(QBrush brush);
    QRectF boundingRect() const;
protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
signals:
        void dellacotian(int index);
private:
        int index;
        QRectF rec;
        QBrush brush;
};

#endif // MYREC_H
