#include "levelchooser.h"

LevelChooser::LevelChooser(Game *parent) :
    Menu(parent)
{
    // set size
    setSceneRect(parent->rect());
    m_width = sceneRect().width()/2;
    setBackgroundBrush(Qt::gray);

    // sets button attributes
    b_margin = 20;
    b_width = m_width - b_margin*2;
    b_height = 60;

    // buttons for level chooser
    QVector<QString> levels = parent->levelList();

    // because of laziness, maximum amount of levels is 7 (else they will be positioned outside Xx768 resolution..
    int levellimit = 7;
    for(int i = 0; i < levels.size() && i < levellimit; i++) {
        Button* button = new Button(b_width, b_height, levels[i], Button::GFunctionPlayLevel);
        button->levelKey(i);
        buttons.append(button);
    }

    buttons.append(new Button(b_width, b_height, "Back to Main Menu", Button::GFunctionMainMenu));

    addButtons(buttons);
}

LevelChooser::~LevelChooser() {

}
