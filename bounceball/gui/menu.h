#ifndef MENU_H
#define MENU_H

#include "engine/game.h"
#include "gui/button.h"
#include <QDir>

class Menu : public QGraphicsScene
{
    QPixmap background;
protected:
    qreal m_width; // menu width
    qreal b_width; // button width
    qreal b_height; // button height
    qreal b_margin; // button margin (top)
    qreal logo_height;
    qreal offset_top; // how much offset from top
    QVector<Button*> buttons;
    void addButtons(QVector<Button*> &b_vector);
    const static QDir soundDir;
    virtual void drawBackground(QPainter *painter, const QRectF &rect);
public:
    Menu(Game* parent=0);
    virtual ~Menu();
};

#endif // MENU_H
