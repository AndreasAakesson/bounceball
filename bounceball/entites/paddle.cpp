#include "paddle.h"

#include "entites/ball.h" // for type-check
#include "engine/level.h" // for casting
#include <iostream> // slett
using namespace std; // slett
Paddle::Paddle(qreal width, qreal height) :
    GameObject(width, height)
{
    setSound("paddle_hit.wav");
}

void Paddle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::blue);
    int corner = height()/4;
    painter->drawRoundedRect(boundingRect(), corner, corner);
}

QPainterPath Paddle::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Paddle::advance(int step) {
    if(!step)
        return;
}

void Paddle::handleCollision(GameObject* gobject, int number) {
    Level* level = dynamic_cast<Level*>(scene());
    if(!level)
        throw std::runtime_error("Paddle cannot recognize Level, exiting...");

    // colliding with ball
    if(gobject->type() == Ball::Type) {
        level->notifyBallPaddleCollision();
        playSound();
    }
}

Paddle::~Paddle() {

}
