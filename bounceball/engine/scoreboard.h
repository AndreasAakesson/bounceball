#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsTextItem>

class ScoreBoard
{
    long score; // current score(points)
    double score_multiplier; // score multiplier
    long ball_paddle_hits; // how many times ball hit paddle
    long ball_brick_hits; // how many times ball hit a brick
    QGraphicsTextItem* v_score;
    QGraphicsTextItem* v_smultiplier;

    //long highscore; // not in use
public:
    ScoreBoard();
    void addPoints(int pts);
    void addSBtoScene(QGraphicsScene* scene);
    long currentScore();
    long ballPaddleHits();
    long ballBrickHits();

    void SMultiplier(double multipl);
    double SMultiplier();

    void incSMultiplier(double multipl = 0.5);
    void resetSMultiplier();

    void notifyBallPaddleCollision();
    void notifyBallBrickCollision();
    virtual ~ScoreBoard();
};

#endif // SCOREBOARD_H
