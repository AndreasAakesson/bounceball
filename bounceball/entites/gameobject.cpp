#include "gameobject.h"

#include <stdexcept>

#ifdef Q_OS_MACX
const QDir GameObject::soundDir = QDir("../Resources/audio/gameobject");
#else
const QDir GameObject::soundDir = QDir("./audio/gameobject");
#endif

GameObject::GameObject(qreal width, qreal height)
{
    width_ = width;
    height_ = height;
}

QRectF GameObject::boundingRect() const {
    //return QRectF(-w/2,-h/2,w,h);
    return QRectF(0,0,width_,height_);
}

qreal GameObject::width() {
    return width_;
}

qreal GameObject::height() {
    return height_;
}

void GameObject::setSound(QString audiofile) {
    soundfx = audiofile;
}

void GameObject::playSound() {
    if(!soundfx.isNull())
        playSound(soundfx);
}

void GameObject::playSound(QString audiofile) {
    QSound::play(soundDir.absolutePath().append("/").append(audiofile));
}

GameObject::~GameObject() {

}
