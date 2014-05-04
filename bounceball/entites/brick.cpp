#include "brick.h"

#include "entites/ball.h" // for collision detection
#include "engine/level.h" // number of columns and rows
#include "engine/game.h" // for width and height
#include <stdexcept>

#include <iostream> // slett
using namespace std; // slett

const int Brick::MaxHealth = 5;
int Brick::PointsHit = 10;
int Brick::PointsBreak = 50;

const QColor Brick::colors[Brick::MaxHealth+1] = {
    Qt::black,  // 0 (wont show)
    Qt::yellow, // 1
    Qt::green,  // 2
    Qt::red,    // 3
    Qt::blue,   // 4
    Qt::gray    // 5
};

Brick::Brick(int healthpts) :
    GameObject(
        Game::Width / Level::BrickCols,
        Game::Height/2 / Level::BrickRows)
{
    health = (healthpts > MaxHealth) ? MaxHealth : healthpts;
    setSound("brick_hit.wav");
}

void Brick::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(colors[health]);
    painter->drawRect(boundingRect());
}

QPainterPath Brick::shape() const {
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Brick::advance(int step) {
    if(!step)
        return;
    if(health <= 0)
        destroy();
}

void Brick::handleCollision(GameObject* gobject, int damage) {

    // colliding with Ball
    if(gobject->type() == Ball::Type) {
        Level* level = dynamic_cast<Level*>(scene());
        if(!level)
            throw std::runtime_error("Brick cannot recognize Level, exiting...");

        health -= damage;

        if(health > 0) {
            level->addPoints(PointsHit);
            update();
            playSound();
        }
        else {
            level->addPoints(PointsBreak);
            playSound("brick_destroy.wav");
            // tell level to check if finished
        }
        level->notifyBallBrickCollision();
    }
}

void Brick::destroy() {
    Level* level = dynamic_cast<Level*>(scene());
    if(!level)
        throw std::runtime_error("Brick cannot recognize Level, exiting...");

    scene()->removeItem(this);

    level->notifyBrickDestroyed();
    delete this;
}

Brick::~Brick() {
    //cout << "Brick deconstructed." << endl;
}
