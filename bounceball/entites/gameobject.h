#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QtGui> // for painting
#include <stdexcept>
#include <QSound>
#include <QString>

class Level;

class GameObject : public QGraphicsItem
{
    QString soundfx;
    qreal width_;
    qreal height_;
    const static QDir soundDir;
public:
    GameObject(qreal width, qreal height);

    QRectF boundingRect() const; // used for calculating size etc.
    enum { Type = QVariant::UserType + 1000 }; // starts at 1000
    int type() const { return Type; } // inherited, enables the use of qgraphicsitem_cast with this item.

    virtual void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget)=0; // inherited, used for painting objects on scene.
    virtual QPainterPath shape() const=0; // inherited, used for collision etc.

    virtual void handleCollision(GameObject* gobject, int helper)=0; // function to handle collisions

    qreal width();
    qreal height();

    virtual ~GameObject();
protected:
    virtual void advance(int step)=0; // inherited, used to animate objects on scene.
    virtual void setSound(QString audiofile); // set soundfx
    virtual void playSound(); // play soundfx
    void playSound(QString audiofile); // play given file
    //Level* level();
};

#endif // GAMEOBJECT_H
