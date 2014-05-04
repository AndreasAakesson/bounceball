#include "pausemenu.h"

PauseMenu::PauseMenu(Game *parent) :
    Menu(parent)
{
    // set size
    setSceneRect(parent->rect());
    m_width = sceneRect().width()/2;
    setBackgroundBrush(Qt::gray);

    // sets button attributes
    b_margin = 20;
    b_width = m_width - b_margin*2;
    b_height = 100;

    // buttons for pause menu
    buttons.append(new Button(b_width, b_height, "Resume", Button::GFunctionResumeLevel));
    buttons.append(new Button(b_width, b_height, "Exit Level", Button::GFunctionExitLevel));

    addButtons(buttons);
}

PauseMenu::~PauseMenu() {

}
