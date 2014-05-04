#include "levelfailed.h"

LevelFailed::LevelFailed(Game *parent) :
    LevelEndMenu(parent)
{
    end_message->setPlainText("Defeat!");
    setBackgroundBrush(Qt::red);

    QSound::play(soundDir.absolutePath().append("/").append("defeat.wav"));
}

LevelFailed::~LevelFailed() {

}
