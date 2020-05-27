#ifndef MYREC_H
#define MYREC_H
#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>



class Myrec :public QGraphicsObject
{
    Q_OBJECT
public:
    Myrec(int x,int y,int w,int h,int index);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    void setBrush(QBrush brush);
    QRectF boundingRect() const override;
protected:
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
signals:
        void dellacotian(int index);
        void table(int index);
private:
        int index;
        QRectF rec;
        QBrush brush;
};

#endif // MYREC_H
