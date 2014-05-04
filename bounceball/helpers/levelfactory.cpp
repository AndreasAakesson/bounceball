#include "levelfactory.h"
#include "engine/game.h" // for width & height

#include <iostream> // slett
using namespace std; // slett

LevelFactory::LevelFactory(QGraphicsView *parent, BrickFactory::FactoryType brickfactory)
{
    // decide what type of bricks this factory is gonna create
    brick_factory = BrickFactory(brickfactory);

    // parent for level
    this->parent_ = parent;
}

Level* LevelFactory::createLevel(QString levelname, QDir levelpath) {
    Level* level;

    LevelFile levelfile(QString(levelpath.absolutePath() + "/" + levelname));

    // create bricks from file if level is valid
    if(levelfile.isValid(Level::BrickRows, Level::BrickCols)) {
        // print out created map
        cout << "Creating " << levelname.toStdString() << ":" << endl
                << levelfile.toQString().toStdString() << endl;

        level = new Level(parent_);
        addBricks(levelfile, level); // from levelfile to level
        createBall(level);
        createPaddle(level);
    }

    // else return test level (lazy error handling...)
    else {
        level = createTestLevel();
    }

    return level;
}

Level* LevelFactory::createTestLevel() {
    Level* level = new Level(parent_);

    int colWidth = Game::Width / Level::BrickCols;
    int colHeight = Game::Height/2 / Level::BrickRows;

    int hp = Brick::MaxHealth;
    // offset by 1 - first row empty
    for(int i = 1; i < Level::BrickRows && hp > 0; i++) {
        // offset by 1, first and last column empty
        for(int j = 1; j < Level::BrickCols-1; j++) {
            Brick* brick = new Brick(hp);
            level->addItem(brick);
            brick->setPos(colWidth*j, colHeight*i);
        }
        hp--;
    }

    createBall(level);
    createPaddle(level);

    return level;
}

void LevelFactory::createBall(Level* level) {
    Ball* ball = new Ball(15, 12.0);
    level->addItem(ball);
    ball->setPos(level->width()/2,level->height()/2 + 100);
}

void LevelFactory::createPaddle(Level *level) {
    Paddle* paddle = new Paddle(180,20);
    level->addItem(paddle);
    level->setPaddle(paddle);
    paddle->setPos(level->width()/2 - paddle->width()/2, level->height()-100);
}

void LevelFactory::addBricks(LevelFile &source, Level *target) {

    int col_w = Game::Width / Level::BrickCols;
    int col_h = (Game::Height/2) / Level::BrickRows;

    // loop through each row
    for(int row = 0; row < Level::BrickRows; row++) {
        // loop through each col
        for(int col = 0; col < Level::BrickCols; col++) {
            // read hp
            int hp = source(row,col);
            // if there is a brick to be created
            if(hp > 0) {
                Brick* brick = brick_factory.createBrick(hp);
                target->addItem(brick);
                // position according to map
                brick->setPos(col_w*col, col_h*row);
            }
        }
    }
}
