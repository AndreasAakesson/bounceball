#ifndef LEVELFACTORY_H
#define LEVELFACTORY_H

#include "engine/level.h"
#include "helpers/levelfile.h"
#include "helpers/brickfactory.h"

class LevelFactory
{
    BrickFactory brick_factory;
    QGraphicsView* parent_;
public:
    LevelFactory(QGraphicsView* parent = 0,
                 BrickFactory::FactoryType brickfactory = BrickFactory::DefaultBrickFactory);

    Level* createLevel(QString levelname, QDir levelpath = Level::LevelPath); // creates a level
    Level* createTestLevel(); // for testing purpose

    void createBall(Level *level); // create default ball
    void createPaddle(Level *level); // create default paddle
    void addBricks(LevelFile &source, Level* target); // add bricks from file to level
};

#endif // LEVELFACTORY_H
