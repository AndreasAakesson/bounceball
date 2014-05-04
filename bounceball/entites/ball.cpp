#include "ball.h"

#include <QGraphicsScene>

#include "entites/paddle.h" // for type-check
#include "entites/brick.h" // for type-check
#include "engine/level.h" // for calling
#include <stdexcept>

#include <iostream> // slett
using namespace std; // slett
Ball::Ball(qreal radius, float ballspeed) :
    GameObject(radius, radius)
{
    velocity.x(0);
    velocity.y(1);
    // not sure if needed, but to avoid too large movements.
    if(ballspeed > radius)
        ballspeed = radius;
    speed(ballspeed);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());
}

QPainterPath Ball::shape() const {
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}

void Ball::advance(int step) {
    if(!step)
        return;

    // retrive limits for "game board"
    QRectF limits = scene()->sceneRect();
    float margin = 2; // 2 pixel margin

    // if ball hits left side
    if(x() < 0 + margin) {
        velocity.invertX();
    }

    // if ball hits right side
    else if(x() > (limits.width() - this->width()) - margin) {
        velocity.invertX();
    }

    // if ball hits the roof
    else if(y() < 0 + margin) {
        velocity.invertY();
    }

    // if ball hits the bottom
    else if(y() > (limits.height() - this->height()) - margin) {
        Level* level = dynamic_cast<Level*>(scene());
        if(!level)
            throw std::runtime_error("Ball is moving on something that isn't a level, exiting...");

        playSound("ball_outside.wav");
        level->ballOutside();
        return;
    }

    else {
        // retrive all items in colliding with the ball
        QList <QGraphicsItem*> items = collidingItems();
        // go through all the items
        int i = 0;
        foreach(QGraphicsItem* item, items) {
            // cast upwards from GraphicItem to GameObject
            GameObject* gobject = dynamic_cast<GameObject*>(item);
            if(gobject)
                handleCollision(gobject, i++);
        }
    }

    // move ball according to velocity
    moveBy(velocity.x()*speed(), velocity.y()*speed());
}

void Ball::handleCollision(GameObject* gobject, int number) {

    // colliding with Paddle
    if(gobject->type() == Paddle::Type) {
        Paddle* paddle = dynamic_cast<Paddle*>(gobject);
        if(!paddle)
            throw runtime_error("Couldn't cast to paddle, exiting.");

        // TODO: Skrive om/lage funksjoner.
        qreal paddleWidth = gobject->boundingRect().width();
        qreal relativeIntersectX = (x() + width()/2) - (gobject->x() + paddleWidth/2);
        qreal normalizedRelativeIntersectionX = (relativeIntersectX/(paddleWidth/2));
        qreal angle = normalizedRelativeIntersectionX * TAU/5; // 72 degrees

        velocity.x(sin(angle));
        velocity.y(-cos(angle));

        paddle->handleCollision(this, 0);
    }

    // Note: Brick collision detection is very lacking.
    // Only solution would be to rather not use collidingItems from Qt,
    // but rather write my own collision detection.
    // This has taken up way too much time. Has to cut it to get the game finished.
    else if(gobject->type() == Brick::Type) {
        Brick* brick = dynamic_cast<Brick*>(gobject);
        if(!brick)
            throw runtime_error("Couldn't cast to brick, exiting.");


        // only change direction for first brick (avoid changing direction more than once)
        if(number == 0) {
            // top
            if(scene()->itemAt(x()+width()/2, y(), sceneTransform()) == brick)
                velocity.invertY();
            // bottom
            else if(scene()->itemAt(x()+ width()/2, y() + height()/2, sceneTransform()) == brick)
                velocity.invertY();
            // right
            else if(scene()->itemAt(x() + width(), y() + height()/2, sceneTransform()) == brick)
                velocity.invertX();
            else if(scene()->itemAt(x(), y() + height()/2, sceneTransform()) == brick)
                velocity.invertX();
        }
        brick->handleCollision(this, 1);
        /*
        // checking for line intersections to decide what side of brick is hit.
        // formula: y=ax+b

        // find balls last position
        qreal x1 = x() - velocity.x()*speed();
        qreal y1 = y() - velocity.y()*speed();
        QPointF lastPos(x1, y1);

        qreal a = (x()-x1) / (y()-y1);
        qreal b = y()-a*x();

        // draw line intersection line
        QLineF balltravel(lastPos, pos());

        // check all sides
        QRectF brickrect = gobject->boundingRect();
        qreal intersect;
        // left
        intersect = a * brickrect.left() + b;
        if(brickrect.top() < intersect && intersect < brickrect.bottom())
            velocity.invertX();

        qreal left = brickrect.left();
        qreal top = brickrect.top();
        qreal right = brickrect.bottomRight().x();
        qreal bottom = brickrect.bottomRight().y();


        float wy = (width() + brick->width()) * (height()/2 - brick->height()/2);
        float hx = (height() + brick->height()) * (width()/2 - brick->width()/2);

        if (wy > hx) {
            if (wy > -hx) {
                velocity.invertY();
                cout << "top" << endl;
            }
            else {
                velocity.invertX();
                cout << "left" << endl;
            }
        }
        else {
            if (wy > -hx) {
                velocity.invertX();
                cout << "right" << endl;
            }
            else {
                velocity.invertY();
                cout << "bottom" << endl;
            }
        }
        */
    }
}

Ball::~Ball() {

}
