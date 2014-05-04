#include "level.h"

#include <engine/game.h> // for FPS

#include <iostream> // slett
#include <stdexcept>

#ifdef Q_OS_MACX
const QDir Level::LevelPath = QDir("../Resources/levels", "level_*");
#else
const QDir Level::LevelPath = QDir("./levels", "level_*");
#endif


const int Level::BrickCols = 16;
const int Level::BrickRows = 16;

Level::Level(QGraphicsView *parent) :
    QGraphicsScene(parent)
{
    paddle_ = 0;
    // sets the scene size
    setSceneRect(parent->rect());

    // image background?
    setBackgroundBrush(Qt::black);

    // init data
    life = 3;
    SMultiplier(1.0);
    addSBtoScene(this);

    // set pause msg
    QFont font("Courier", 24, QFont::Bold);
    pause_msg = new QGraphicsTextItem("Press space to start.");
    pause_msg->setDefaultTextColor(Qt::red);
    pause_msg->setFont(font);
    addItem(pause_msg);
    pause_msg->setPos((width() / 2) - pause_msg->boundingRect().width()/2, height() / 2);

    timer = new QTimer(this);
    timer->setInterval(Game::FPS);
    connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
}

void Level::start() {
    timer->start();
    if(pause_msg->isVisible())
        pause_msg->hide();
}

void Level::pause() {
    timer->stop();
    if(!pause_msg->isVisible())
        pause_msg->show();
    // space to start?
}

bool Level::isRunning() {
    return timer->isActive();
}

void Level::ballOutside() {
    life--;
    Game* game = dynamic_cast<Game*>(views().at(0));
    if(!game)
        throw std::runtime_error("Level cannot recognize Game, exiting...");

    if(life > 0) {
        game->resetLevel();
        paddle_->setPos(width()/2 - paddle_->width()/2, paddle_->y());
        pause();
    }
    else
        gameOver();

}

bool Level::finished() {
    QList<QGraphicsItem*> gameobjects = items();

    foreach(QGraphicsItem* item, gameobjects) {
        if(item->type() == Brick::Type) {
            return false;
        }
    }
    return true;
}

QString Level::fromFile() {
    return from_file;
}

void Level::fromFile(QString filename) {
    from_file = filename;
}

void Level::notifyBrickDestroyed() {
    if(finished()) {
        Game* game = dynamic_cast<Game*>(views().at(0));
        if(!game)
            throw std::runtime_error("Level cannot recognize Game, exiting...");

        // tell game that level is completed
        game->levelEnded(Completed);
    }
}

void Level::gameOver() {
    Game* game = dynamic_cast<Game*>(views().at(0));
    if(!game)
        throw std::runtime_error("Level cannot recognize Game, exiting...");

    // tell game that level failed
    game->levelEnded(Failed);
}

void Level::removeGameObject(int gobjectType) {
    QList<QGraphicsItem*> gameobjects = items();

    foreach(QGraphicsItem* item, gameobjects) {
        if(item->type() == gobjectType) {
            removeItem(item);
            delete item;
        }
    }
}

void Level::setPaddle(Paddle *paddle) {
    if(paddle_)
        delete paddle_;
    paddle_ = paddle;
}

void Level::movePaddle(float x) {
    // avoid moving outside
    if(x < 0)
        x = 0;
    else if(x > (sceneRect().width() - paddle_->width()))
        x = sceneRect().width()-paddle_->width();
    // only move horizontal
    paddle_->setPos(x, paddle_->y());
}

void Level::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // if game is running
    if(isRunning())
        movePaddle(event->scenePos().x());
}

Level::~Level() {
    if(isRunning())
        timer->stop();
    delete timer;
    delete paddle_;
    clear();
}
