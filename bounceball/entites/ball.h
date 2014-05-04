#ifndef BALL_H
#define BALL_H

#include "entites/gameobject.h"
#include "entites/is_vector.h"

class Ball : public GameObject, isVector
{
public:
    Ball(qreal radius, float ballspeed = 12.0);
    enum { Type = GameObject::Type + 1 }; // ItemNO: 1
    int type() const { return Type; }

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

    void handleCollision(GameObject* gobject, int number);

    ~Ball();
protected:
    void advance(int step);
};

#endif // BALL_H
