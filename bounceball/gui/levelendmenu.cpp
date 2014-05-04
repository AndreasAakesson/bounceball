#include "levelendmenu.h"
#include <QSound>

LevelEndMenu::LevelEndMenu(Game *parent) :
    Menu(parent)
{
    // set size
    setSceneRect(parent->rect());
    m_width = sceneRect().width()/2;
    setBackgroundBrush(Qt::gray);

    // sets button attributes
    b_margin = 20;
    b_width = m_width - b_margin*2;
    b_height = 100;

    // just made quick, should've made own function addText() to clean this up...
    // end msg
    QFont font("Arial", 36, QFont::Bold);
    end_message = new QGraphicsTextItem(QString("Placeholder"));
    end_message->setFont(font);
    addItem(end_message);
    end_message->setPos(m_width - b_width/2, offset_top);
    offset_top += end_message->boundingRect().height();

    // score msg
    long score = parent->level().currentScore();
    end_score = new QGraphicsTextItem(QString("Your score: ").append(QString::number(score)));
    addItem(end_score);
    end_score->setPos(m_width - b_width/2, offset_top);
    offset_top += end_score->boundingRect().height();

    // paddlehit msg
    long paddlehits = parent->level().ballPaddleHits();
    end_hits = new QGraphicsTextItem(QString("Ball-Paddle hits: ").append(QString::number(paddlehits)));
    addItem(end_hits);
    end_hits->setPos(m_width - b_width/2, offset_top);
    offset_top += end_hits->boundingRect().height();

    /* Nvm this...
    // hitrate msg
    long brickhits = parent->level().ballBrickHits();
    qreal hitrate = ((double) brickhits/paddlehits);
    end_hitrate = new QGraphicsTextItem(QString("Hitrate: ").append(QString::number(hitrate).append(" bricks per paddle-hit.")));
    addItem(end_hitrate);
    end_hitrate->setPos(m_width - b_width/2, offset_top);
    offset_top += end_hitrate->boundingRect().height();
    */

    // buttons for end menu
    buttons.append(new Button(b_width, b_height, "Restart Level", Button::GFunctionRestartLevel));
    buttons.append(new Button(b_width, b_height, "Exit to Main Menu", Button::GFunctionExitLevel));

    addButtons(buttons);
}

void LevelEndMenu::drawBackground(QPainter *painter, const QRectF &rect) {
    QGraphicsScene::drawBackground(painter, rect);
}

LevelEndMenu::~LevelEndMenu() {
    delete end_message;
    delete end_score;
    delete end_hits;
}
