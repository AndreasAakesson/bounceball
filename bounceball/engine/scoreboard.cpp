#include "scoreboard.h"
#include <QGraphicsScene>

ScoreBoard::ScoreBoard()
{
    score = 0;
    score_multiplier = 1.0;
    ball_paddle_hits = 0;

    QFont font("Courier", 24, QFont::Bold);
    v_score = new QGraphicsTextItem(QString().setNum(score));
    v_score->setDefaultTextColor(Qt::yellow);
    v_score->setFont(font);

    v_smultiplier = new QGraphicsTextItem(QString().setNum(score_multiplier).append("x"));
    v_smultiplier->setDefaultTextColor(Qt::yellow);
    v_score->setFont(font);
}


void ScoreBoard::addPoints(int pts) {
    score += pts*score_multiplier;
    v_score->setPlainText(QString().setNum(score));
}

void ScoreBoard::addSBtoScene(QGraphicsScene *scene) {
    scene->addItem(v_score);
    v_score->setPos(5, scene->height() - (v_score->boundingRect().height()+5));
    scene->addItem(v_smultiplier);
    v_smultiplier->setPos(5, scene->height() - (v_score->boundingRect().height()+20));
}

long ScoreBoard::currentScore() {
    return score;
}

long ScoreBoard::ballPaddleHits() {
    return ball_paddle_hits;
}

long ScoreBoard::ballBrickHits() {
    return ball_brick_hits;
}

double ScoreBoard::SMultiplier() {
    return score_multiplier;
}

void ScoreBoard::SMultiplier(double multipl) {
    score_multiplier = multipl;
    v_smultiplier->setPlainText(QString().setNum(score_multiplier).append("x"));
}

void ScoreBoard::incSMultiplier(double multipl) {
    SMultiplier(multipl + score_multiplier);
}

void ScoreBoard::resetSMultiplier() {
    SMultiplier(1.0);
}

void ScoreBoard::notifyBallPaddleCollision() {
    ball_paddle_hits++;
    resetSMultiplier();
}

void ScoreBoard::notifyBallBrickCollision() {
    ball_brick_hits++;
    incSMultiplier(0.5);
}

ScoreBoard::~ScoreBoard() {
    // handled by ~Level
    /*
    delete v_score;
    delete v_smultiplier;
    */
}
