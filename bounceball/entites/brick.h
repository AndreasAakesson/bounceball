#ifndef BRICK_H
#define BRICK_H

#include "entites/gameobject.h"

class Brick : public GameObject
{
    int health;
    const static QColor colors[];
public:
    Brick(int healthpts);
    enum { Type = GameObject::Type + 3 }; // ItemNO: 3
    int type() const { return Type; }
    const static int MaxHealth; // Max health for bricks;
    static int PointsHit;
    static int PointsBreak;

    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QPainterPath shape() const;

    void handleCollision(GameObject* gobject, int damage);

    ~Brick();
protected:
    void advance(int step);

private:
    void destroy();
};

#endif // BRICK_H
