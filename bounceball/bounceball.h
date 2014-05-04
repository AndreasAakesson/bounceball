#ifndef BOUNCEBALL_H
#define BOUNCEBALL_H

#include <QMainWindow>
#include "engine/game.h"

class Bounceball : public QMainWindow
{
    Q_OBJECT

    Game* game_; // game engine
public:
    //explicit Bounceball(QWidget *parent = 0);
    Bounceball(int width, int height);
    void run();

signals:

public slots:

};

#endif // BOUNCEBALL_H
