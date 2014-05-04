#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsSceneMouseEvent>
#include <QSoundEffect>
#include "entites/gameobject.h"

class Paddle : public GameObject
{
public:
    Paddle(qreal width, qreal height);
    enum { Type = GameObject::Type + 2 }; // ItemNO: 2
    int type() const { return Type; }

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

    void handleCollision(GameObject* gobject, int number);

    ~Paddle();
protected:
    void advance(int step);
};

#endif // PADDLE_H
