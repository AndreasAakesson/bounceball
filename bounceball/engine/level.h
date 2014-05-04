#ifndef LEVEL_H
#define LEVEL_H

#include <QGraphicsScene> // inherits
#include <QGraphicsView> // parameter
#include <QTimer> // for animating
#include <QString>

#include "entites/paddle.h"
#include "entites/ball.h"
#include "entites/brick.h"
#include "engine/scoreboard.h"

class Level : public QGraphicsScene, public ScoreBoard
{
    Q_OBJECT
    int life; // current lives
    QString from_file; // to id the level

    QTimer* timer;
    Paddle* paddle_;
    QGraphicsTextItem* pause_msg;
public:
    Level(QGraphicsView* parent = 0);

    enum EndState {
        Completed,
        Failed
    };

    const static QDir LevelPath;
    const static int BrickCols; // number of columns for bricks
    const static int BrickRows; // number of rows for bricks

    void start(); // level is active
    void pause(); // level is inactive
    bool isRunning();
    bool finished(); // check if level is finished
    void setPaddle(Paddle* paddle); // sets pointer to player paddle
    void ballOutside(); // subtract 1 life
    void removeGameObject(int gobjectType);
    void notifyBrickDestroyed(); // check if level is finished and tell game
    QString fromFile(); // returns id for level
    void fromFile(QString filename); // sets id for level

    ~Level();
private:
    void movePaddle(float x);
    void gameOver();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // LEVEL_H
