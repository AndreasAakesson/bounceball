#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsItem>
#include <QPainter>

class Button : public QGraphicsItem
{
public:
    enum GameFunction {
        GFunctionNone,
        GFunctionMainMenu, // show main menu
        GFunctionQuickStart, // start random level
        GFunctionTestLevel, // start test level
        GFunctionLevelChooser, // level chooser menu
        GFunctionPlayLevel, // play level given buttons level_key
        GFunctionResumeLevel, // resume current level
        GFunctionRestartLevel, // restart the current level
        GFunctionExitLevel, // exit current level
        GFunctionExitGame // exit game
    };

private:
    QString label_;
    QColor m_brush;
    QColor m_pen;
    qreal width_;
    qreal height_;
    GameFunction gfunction;
    int level_key; // key to use together with levels for lookup in levellist
    const static QString soundfx;

public:
    Button(qreal width, qreal height, QString label, Button::GameFunction function = GFunctionNone);

    QRectF boundingRect() const;

    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    QString label();
    GameFunction gameFunction();
    void levelKey(int key); // sets level key
    int levelKey(); // returns level key
    void playSound();

    ~Button();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    //void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

#endif // BUTTON_H
