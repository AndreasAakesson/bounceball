#include "button.h"

#include <iostream> // slett
#include <QDir>
#include <QSound>

#ifdef Q_OS_MACX
const QString Button::soundfx = QDir("../Resources/audio/gui").absolutePath().append("/").append("button.wav");
#else
const QString Button::soundfx = QDir("./audio/gui").absolutePath().append("/").append("button.wav");
#endif

Button::Button(qreal width, qreal height, QString label, GameFunction function)
{
    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
    label_ = label;
    width_ = width;
    height_ = height;
    m_brush = Qt::black;
    m_pen = Qt::white;
    gfunction = function;

    level_key = -1; // == no level bound to this button
}

QRectF Button::boundingRect() const {
    return QRectF(0,0,width_,height_);
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // background
    painter->setBrush(m_brush);
    painter->drawRect(boundingRect());

    // label
    QFont font("Courier", 24, QFont::Bold );
    painter->setPen(m_pen);
    painter->setFont(font);
    painter->drawText(boundingRect(), Qt::AlignCenter, label_);
}

QString Button::label() {
    return label_;
}

Button::GameFunction Button::gameFunction() {
    return gfunction;
}

void Button::levelKey(int key) {
    level_key = key;
}

int Button::levelKey() {
    return level_key;
}

void Button::playSound() {
    QSound::play(soundfx);
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    m_pen = Qt::red;
    update();
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    m_pen = Qt::white;
    update();
}

Button::~Button() {

}

/*
void Button::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    setFocus(Qt::MouseFocusReason);
    std::cout << label_.toStdString() << std::endl;
    //clicked();
}*/
