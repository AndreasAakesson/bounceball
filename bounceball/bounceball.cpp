#include "bounceball.h"
#include <QDesktopWidget>

Bounceball::Bounceball(int width, int height) :
    QMainWindow()
{
    // Add title
    setWindowTitle("Bounceball");

    // Set size for window
    setFixedSize(width,height);

    // Position window to center
    QDesktopWidget wid;
    int screenWidth = wid.screen()->width();
    int screenHeight = wid.screen()->height();
    setGeometry((screenWidth/2)-(width/2),(screenHeight/2)-(height/2),width,height);

    show();

}

void Bounceball::run() {
    game_ = new Game(width(), height(), this);
    game_->init();
}
