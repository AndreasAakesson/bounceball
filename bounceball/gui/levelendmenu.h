#ifndef LEVELENDMENU_H
#define LEVELENDMENU_H

#include "gui/menu.h"
#include <QGraphicsTextItem>

class LevelEndMenu : public Menu
{
public:
    LevelEndMenu(Game *parent=0);

    virtual ~LevelEndMenu();

protected:
    QGraphicsTextItem* end_message;
    QGraphicsTextItem* end_score;
    QGraphicsTextItem* end_hits;
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
    //QGraphicsTextItem* end_hitrate; // no time to fix
};

#endif // LEVELENDMENU_H
