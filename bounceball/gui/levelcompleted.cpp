#include "levelcompleted.h"

LevelCompleted::LevelCompleted(Game *parent) :
    LevelEndMenu(parent)
{
    end_message->setPlainText("Congratulations!");
    setBackgroundBrush(Qt::green);

    QSound::play(soundDir.absolutePath().append("/").append("success.wav"));
}

LevelCompleted::~LevelCompleted() {

}
